#include "AI/Task/Knight/BTTask_KnightAttack.h"
#include "Actor/EnemyController/Knight/KnightController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_KnightAttack::UBTTask_KnightAttack()
{
	IsAttackRequestedKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, IsAttackRequestedKey));
	IsAttackingKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, IsAttackingKey));
}

EBTNodeResult::Type UBTTask_KnightAttack::ExecuteTask(
	UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{


	// Get BlackboardComponent
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// ���� ��û�� �޾����Ƿ� ó��
	blackboardComponent->SetValueAsBool(IsAttackRequestedKey.SelectedKeyName, false);

	// ������ ���·� ��ȯ
	blackboardComponent->SetValueAsBool(IsAttackingKey.SelectedKeyName, true);

	

	// Get KnightController
	AKnightController* controller = Cast<AKnightController>(ownerComponent.GetOwner());

	// ��Ʈ�ѷ� ��ü�� ��ȿ���� ���� ��� �ൿ ����.
	if (!IsValid(controller))
	{
		return  EBTNodeResult::Failed;
	}


	// ���� ����
	controller->Attack();

	// �ൿ ����
	return EBTNodeResult::Succeeded;
}
