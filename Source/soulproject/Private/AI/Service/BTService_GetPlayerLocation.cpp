#include "AI/Service/BTService_GetPlayerLocation.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_GetPlayerLocation::UBTService_GetPlayerLocation()
{
	PlayerActorKey.AddObjectFilter(
		this, 
		GET_MEMBER_NAME_CHECKED(ThisClass, PlayerActorKey), 
		UObject::StaticClass());
	TargetLocationKey.AddVectorFilter(
		this, 
		GET_MEMBER_NAME_CHECKED(ThisClass, TargetLocationKey));
}

void UBTService_GetPlayerLocation::TickNode(
	UBehaviorTreeComponent& ownerComponent,
	uint8* nodeMemory,
	float dt)
{
	// Call Parent Member Function
	Super::TickNode(ownerComponent, nodeMemory, dt);

	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// 플레이어 캐릭터를 얻습니다.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(blackboardComponent->GetValueAsObject(
		PlayerActorKey.SelectedKeyName));

	// 얻은 플레이어 캐릭터가 유효하지 않은 경우, 함수 호출 종료
	if (!IsValid(gameCharacter)) return;

	// 현재 위치를 얻습니다.
	AController* enemyController = Cast<AController>(blackboardComponent->GetOwner());
	FVector currentLocation = enemyController->GetPawn()->GetActorLocation();

	// 적 캐릭터가 Dragon(보스) 인 경우와 그 외 적캐릭터의 경우 목표 위치를 다르게 설정합니다.
	ADragonCharacter* dragon = Cast<ADragonCharacter>(enemyController->GetPawn());
	if (IsValid(dragon))
	{
		FVector Dragondirection = gameCharacter->GetActorLocation() - currentLocation;
		Dragondirection.Z = 0.0f;
		Dragondirection.Normalize();

		// 목표 위치를 플레이어 위치보다 조금 더 뒤로 설정합니다.
		TargetLocation = gameCharacter->GetActorLocation() - Dragondirection * 1000.0f;
	}
	else
	{
		// 플레이어 위치를 얻어 목표 위치로 사용합니다.
		TargetLocation = gameCharacter->GetActorLocation() - FVector(1.0);
	}


	if (bUseMaxTrackingDistance)
	{

		// 최대 추적 거리
		float maxTrackingDistance = 500.0f;

		// 최소 추적 거리
		float minTrackingDistance = 100.0f;

		// 목표 위치까지의 거리가 최대 추적 거리를 초과하는지 확인합니다.
		if (FVector::Distance(currentLocation, TargetLocation) > maxTrackingDistance)
		{
			// 목표 위치까지의 방향을 얻습니다.
			FVector direction = (TargetLocation - currentLocation).GetSafeNormal();

			// 최대 추적 거리를 적용합니다.
			TargetLocation = currentLocation + direction * maxTrackingDistance;
		}

		
		// 목표 위치까지의 방향을 얻습니다.
		FVector direction = (TargetLocation - currentLocation).GetSafeNormal();

		// 최소 추적 거리를 적용합니다.
		TargetLocation = TargetLocation - direction * minTrackingDistance;
		
	}

	// 목표 위치를 설정합니다.
	blackboardComponent->SetValueAsVector(
		TargetLocationKey.SelectedKeyName, TargetLocation);
}

