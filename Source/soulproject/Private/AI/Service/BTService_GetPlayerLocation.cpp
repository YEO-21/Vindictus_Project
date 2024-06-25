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

	// �÷��̾� ĳ���͸� ����ϴ�.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(blackboardComponent->GetValueAsObject(
		PlayerActorKey.SelectedKeyName));

	// ���� �÷��̾� ĳ���Ͱ� ��ȿ���� ���� ���, �Լ� ȣ�� ����
	if (!IsValid(gameCharacter)) return;

	// ���� ��ġ�� ����ϴ�.
	AController* enemyController = Cast<AController>(blackboardComponent->GetOwner());
	FVector currentLocation = enemyController->GetPawn()->GetActorLocation();

	// �� ĳ���Ͱ� Dragon(����) �� ���� �� �� ��ĳ������ ��� ��ǥ ��ġ�� �ٸ��� �����մϴ�.
	ADragonCharacter* dragon = Cast<ADragonCharacter>(enemyController->GetPawn());
	if (IsValid(dragon))
	{
		FVector Dragondirection = gameCharacter->GetActorLocation() - currentLocation;
		Dragondirection.Z = 0.0f;
		Dragondirection.Normalize();

		// ��ǥ ��ġ�� �÷��̾� ��ġ���� ���� �� �ڷ� �����մϴ�.
		TargetLocation = gameCharacter->GetActorLocation() - Dragondirection * 1000.0f;
	}
	else
	{
		// �÷��̾� ��ġ�� ��� ��ǥ ��ġ�� ����մϴ�.
		TargetLocation = gameCharacter->GetActorLocation() - FVector(1.0);
	}


	if (bUseMaxTrackingDistance)
	{

		// �ִ� ���� �Ÿ�
		float maxTrackingDistance = 500.0f;

		// �ּ� ���� �Ÿ�
		float minTrackingDistance = 100.0f;

		// ��ǥ ��ġ������ �Ÿ��� �ִ� ���� �Ÿ��� �ʰ��ϴ��� Ȯ���մϴ�.
		if (FVector::Distance(currentLocation, TargetLocation) > maxTrackingDistance)
		{
			// ��ǥ ��ġ������ ������ ����ϴ�.
			FVector direction = (TargetLocation - currentLocation).GetSafeNormal();

			// �ִ� ���� �Ÿ��� �����մϴ�.
			TargetLocation = currentLocation + direction * maxTrackingDistance;
		}

		
		// ��ǥ ��ġ������ ������ ����ϴ�.
		FVector direction = (TargetLocation - currentLocation).GetSafeNormal();

		// �ּ� ���� �Ÿ��� �����մϴ�.
		TargetLocation = TargetLocation - direction * minTrackingDistance;
		
	}

	// ��ǥ ��ġ�� �����մϴ�.
	blackboardComponent->SetValueAsVector(
		TargetLocationKey.SelectedKeyName, TargetLocation);
}

