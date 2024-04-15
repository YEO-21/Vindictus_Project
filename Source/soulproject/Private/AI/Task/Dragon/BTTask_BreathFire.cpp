#include "AI/Task/Dragon/BTTask_BreathFire.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Component/DragonCharacterAttackComponent/DragonCharacterAttackComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_BreathFire::UBTTask_BreathFire()
{
	// 틱 기능 활성화
	bNotifyTick = true;
}

void UBTTask_BreathFire::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float dt)
{
	Super::TickTask(ownerComp, nodeMemory, dt);

	
	ADragonCharacter* pawn = Cast<ADragonCharacter>(Cast<AController>(ownerComp.GetOwner())->GetPawn());

	if (!BreathFireStarted)
	{
		if (pawn->GetAttackComponent()->GetBreathFireState())
		{
			BreathFireStarted = true;
		}
		else return;
	}

	if (BreathFireStarted && !pawn->GetAttackComponent()->GetBreathFireState())
	{
		FinishLatentTask(ownerComp, EBTNodeResult::Type::Succeeded);
		BreathFireStarted = false;
	}
}

EBTNodeResult::Type UBTTask_BreathFire::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	AController* controller = Cast<AController>(ownerComponent.GetOwner());
	if (!IsValid(controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("controller is not valid"));
		return EBTNodeResult::Type::Failed;
	}

	ADragonCharacter* dragonCharacter = Cast<ADragonCharacter>(controller->GetPawn());
	if (!IsValid(dragonCharacter)) return EBTNodeResult::Type::Failed;

	// 애니메이션 재생
	dragonCharacter->PlayAttackAnimMontage(ANIMMONTAGE_SECTION_BREATHFIRE);


	return EBTNodeResult::Type::InProgress;
}
