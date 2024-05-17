#include "AI/Task/Wolf/BTTask_WolfAttack.h"

#include "Actor/EnemyController/Wolf/WolfController.h"
#include "Actor/EnemyCharacter/Wolf/WolfCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_WolfAttack::UBTTask_WolfAttack()
{
	
	IsAttackRequestedKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, IsAttackRequestedKey));
	IsAttackingKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, IsAttackingKey));
}

EBTNodeResult::Type UBTTask_WolfAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// ����Ʈ ������Ʈ�� ����ϴ�.
	UBlackboardComponent * blackboardComponent = OwnerComp.GetBlackboardComponent();

	// ���� ��û ó����
	blackboardComponent->SetValueAsBool(IsAttackRequestedKey.SelectedKeyName, false);

	// ������ ���·� �����մϴ�.
	blackboardComponent->SetValueAsBool(IsAttackingKey.SelectedKeyName, true);

	// Get Wolf Controller
	AWolfController* wolfController = Cast<AWolfController>(OwnerComp.GetOwner());

	// ��ȿ�� �˻� ����
	if (!IsValid(wolfController)) return EBTNodeResult::Failed;

	// ���� ����
	wolfController->Attack();

	// �ൿ ����
	return EBTNodeResult::Succeeded;
}
