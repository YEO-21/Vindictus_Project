#include "AI/Task/BTTask_GetRandomLocation.h"

#include "NavigationSystem.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	// 키 필터링
	SpawnLocationKey.AddVectorFilter(this, TEXT("SpawnLocationKey"));
	MaxMoveDistance.AddFloatFilter(this, TEXT("MaxMoveDistance")); 
	ResultLocationKey.AddVectorFilter(this, TEXT("ResultLocationKey"));
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	// Blackboard Component
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// 시작 위치를 얻습니다.
	FVector spawnLocation = blackboardComponent->GetValueAsVector(
		SpawnLocationKey.SelectedKeyName);

	// 최대 이동 거리를 얻습니다.
	float maxMoveDistance = blackboardComponent->GetValueAsFloat(
		MaxMoveDistance.SelectedKeyName);

	// 현재 사용되는 navigationSystem 을 얻습니다.
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(this);
	FNavLocation resultLocation;

	// spawnLocation 을 기준으로 maxMoveDistance 반경 내의 랜덤한 위치를 얻습니다.
	bool bComplete = navSystem->GetRandomPointInNavigableRadius(spawnLocation, maxMoveDistance, resultLocation);

	// 랜덤한 위치를 얻었다면
	if (bComplete)
	{
		// 결과 위치를 저장합니다.
		blackboardComponent->SetValueAsVector(
			ResultLocationKey.SelectedKeyName, resultLocation.Location);
	}

	return bComplete ? EBTNodeResult::Type::Succeeded : EBTNodeResult::Type::Failed;
}
