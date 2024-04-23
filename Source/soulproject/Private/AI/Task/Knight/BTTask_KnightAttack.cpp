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

	// 공격 요청을 받았으므로 처리
	blackboardComponent->SetValueAsBool(IsAttackRequestedKey.SelectedKeyName, false);

	// 공격중 상태로 전환
	blackboardComponent->SetValueAsBool(IsAttackingKey.SelectedKeyName, true);

	

	// Get KnightController
	AKnightController* controller = Cast<AKnightController>(ownerComponent.GetOwner());

	// 컨트롤러 객체가 유효하지 않은 경우 행동 실패.
	if (!IsValid(controller))
	{
		return  EBTNodeResult::Failed;
	}


	// 공격 실행
	controller->Attack();

	// 행동 성공
	return EBTNodeResult::Succeeded;
}
