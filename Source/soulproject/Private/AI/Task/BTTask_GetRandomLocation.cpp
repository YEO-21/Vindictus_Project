#include "AI/Task/BTTask_GetRandomLocation.h"

#include "NavigationSystem.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	// Ű ���͸�
	SpawnLocationKey.AddVectorFilter(this, TEXT("SpawnLocationKey"));
	MaxMoveDistance.AddFloatFilter(this, TEXT("MaxMoveDistance")); 
	ResultLocationKey.AddVectorFilter(this, TEXT("ResultLocationKey"));
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	// Blackboard Component
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// ���� ��ġ�� ����ϴ�.
	FVector spawnLocation = blackboardComponent->GetValueAsVector(
		SpawnLocationKey.SelectedKeyName);

	// �ִ� �̵� �Ÿ��� ����ϴ�.
	float maxMoveDistance = blackboardComponent->GetValueAsFloat(
		MaxMoveDistance.SelectedKeyName);

	// ���� ���Ǵ� navigationSystem �� ����ϴ�.
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(this);
	FNavLocation resultLocation;

	// spawnLocation �� �������� maxMoveDistance �ݰ� ���� ������ ��ġ�� ����ϴ�.
	bool bComplete = navSystem->GetRandomPointInNavigableRadius(spawnLocation, maxMoveDistance, resultLocation);

	// ������ ��ġ�� ����ٸ�
	if (bComplete)
	{
		// ��� ��ġ�� �����մϴ�.
		blackboardComponent->SetValueAsVector(
			ResultLocationKey.SelectedKeyName, resultLocation.Location);
	}

	return bComplete ? EBTNodeResult::Type::Succeeded : EBTNodeResult::Type::Failed;
}
