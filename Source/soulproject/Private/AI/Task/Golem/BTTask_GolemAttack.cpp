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

	// 공격 요청을 받았으므로 처리
	blackboardComponent->SetValueAsBool(IsAttackRequestedKey.SelectedKeyName, false);

	// 공격중 상태로 전환
	blackboardComponent->SetValueAsBool(IsAttackingKey.SelectedKeyName, true);

	// 골렘 컨트롤러를 얻습니다.
	AGolemController* controller = Cast<AGolemController>(ownerComponent.GetOwner());
	if (!IsValid(controller)) return EBTNodeResult::Failed;

	controller->Attack();



	return EBTNodeResult::Type::Succeeded;
}
