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
	// 블랙보트 컴포넌트를 얻습니다.
	UBlackboardComponent * blackboardComponent = OwnerComp.GetBlackboardComponent();

	// 공격 요청 처리됨
	blackboardComponent->SetValueAsBool(IsAttackRequestedKey.SelectedKeyName, false);

	// 공격중 상태로 설정합니다.
	blackboardComponent->SetValueAsBool(IsAttackingKey.SelectedKeyName, true);

	// Get Wolf Controller
	AWolfController* wolfController = Cast<AWolfController>(OwnerComp.GetOwner());

	// 유효성 검사 진행
	if (!IsValid(wolfController)) return EBTNodeResult::Failed;

	// 공격 진행
	wolfController->Attack();

	// 행동 성공
	return EBTNodeResult::Succeeded;
}
