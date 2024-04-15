#include "AI/Task/Dragon/BTTask_ClawAttack.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Component/DragonCharacterAttackComponent/DragonCharacterAttackComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClawAttack::UBTTask_ClawAttack()
{
	// ƽ ��� Ȱ��ȭ
	bNotifyTick = true;
}

void UBTTask_ClawAttack::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float dt)
{
	Super::TickTask(ownerComp, nodeMemory, dt);

	ADragonCharacter* pawn = Cast<ADragonCharacter>(
		Cast<AController>(ownerComp.GetOwner())->GetPawn());


	if (!ClawAttackStarted)
	{
		if (pawn->GetAttackComponent()->GetClawAttackState())
		{
			ClawAttackStarted = true;
		}
		else return;
	}

	if (ClawAttackStarted && !pawn->GetAttackComponent()->GetClawAttackState())
	{
		FinishLatentTask(ownerComp, EBTNodeResult::Type::Succeeded);
		ClawAttackStarted = false;
	}

}

EBTNodeResult::Type UBTTask_ClawAttack::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	// GetPawn
	ADragonCharacter* pawn = Cast<ADragonCharacter>(
		Cast<AController>(ownerComponent.GetOwner())->GetPawn());

	// ��ȿ�� �˻�
	if (!IsValid(pawn)) return EBTNodeResult::Type::Failed;

	// Claw Attack �ִϸ��̼� ���
	pawn->PlayAttackAnimMontage(ANIMMONTAGE_SECTION_CLAWATTACK);

	return EBTNodeResult::Type::InProgress;
}
