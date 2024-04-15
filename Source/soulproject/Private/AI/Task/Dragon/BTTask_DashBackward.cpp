#include "AI/Task/Dragon/BTTask_DashBackward.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Actor/EnemyController/Dragon/DragonController.h"

#include "Component/DragonCharacterMovementComponent/DragonCharacterMovementComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_DashBackward::UBTTask_DashBackward()
{
	IsMoveTaskRunningKey.AddBoolFilter(this,
		GET_MEMBER_NAME_CHECKED(ThisClass, IsMoveTaskRunningKey));

	// ƽ ����� Ȱ��ȭ ��ŵ�ϴ�.
	bNotifyTick = true;
}

void UBTTask_DashBackward::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// GetBlackboardComponent
	UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();

	bool isMoveTaskRunning =
		blackboardComponent->GetValueAsBool(IsMoveTaskRunningKey.SelectedKeyName);

	if (!isMoveTaskRunning)
	{
		// �ൿ ����
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}

EBTNodeResult::Type UBTTask_DashBackward::ExecuteTask(
	UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	// GetBlackboardComponent
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	ADragonController* controller = Cast<ADragonController>(blackboardComponent->GetOwner());
	if (!IsValid(controller)) return EBTNodeResult::Type::Failed;

	ADragonCharacter* dragonCharacter = Cast<ADragonCharacter>(controller->GetPawn());
	if (!IsValid(dragonCharacter)) return EBTNodeResult::Type::Failed;



	blackboardComponent->SetValueAsBool(IsMoveTaskRunningKey.SelectedKeyName, true);

	if (!dragonCharacter->GetDragonMovementComponent()->GetDashState())
	{
		dragonCharacter->GetDragonMovementComponent()->StartDash(
			dragonCharacter->GetActorForwardVector() * -1,
			5000.0f);
	}

	// �ൿ�� ���� ��������!
	return EBTNodeResult::Type::InProgress;
}
