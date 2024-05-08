#include "AI/Task/Golem/BTTask_GolemAttack.h"

#include "Actor/EnemyController/Golem/GolemController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GolemAttack::UBTTask_GolemAttack()
{
	IsAttackRequestedKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, IsAttackRequestedKey));
	IsAttackingKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, IsAttackingKey));
}

EBTNodeResult::Type UBTTask_GolemAttack::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	// Get BlackboardComponent
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// ���� ��û�� �޾����Ƿ� ó��
	blackboardComponent->SetValueAsBool(IsAttackRequestedKey.SelectedKeyName, false);

	// ������ ���·� ��ȯ
	blackboardComponent->SetValueAsBool(IsAttackingKey.SelectedKeyName, true);

	// �� ��Ʈ�ѷ��� ����ϴ�.
	AGolemController* controller = Cast<AGolemController>(ownerComponent.GetOwner());
	if (!IsValid(controller)) return EBTNodeResult::Failed;

	controller->Attack();



	return EBTNodeResult::Type::Succeeded;
}
