#include "AI/Task/Dragon/BTTask_StartSoar.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"

#include "Component/DragonCharacterMovementComponent/DragonCharacterMovementComponent.h"

#include "AnimInstance/DragonCharacter/DragonCharacterAnimInstance.h"


UBTTask_StartSoar::UBTTask_StartSoar()
{
	bNotifyTick = true;
}

void UBTTask_StartSoar::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ADragonCharacter* dragonCharacter = Cast<ADragonCharacter>(
		Cast<AController>(OwnerComp.GetOwner())->GetPawn());

	UDragonCharacterMovementComponent* movementComponent =
		dragonCharacter->GetDragonMovementComponent();

	if (!FlyStarted)
	{
		if (movementComponent->GetFlyState())
		{
			FlyStarted = true;
		}
		return;
	}

	if (FlyStarted && !movementComponent->GetFlyState())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		FlyStarted = false;
	}
}

EBTNodeResult::Type UBTTask_StartSoar::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* newMem)
{
	ADragonCharacter* dragonCharacter = Cast<ADragonCharacter>(
		Cast<AController>(ownerComp.GetOwner())->GetPawn());

	UDragonCharacterMovementComponent* movementComponent =
		dragonCharacter->GetDragonMovementComponent();

	UDragonCharacterAnimInstance* animInst =
		Cast<UDragonCharacterAnimInstance>(dragonCharacter->GetMesh()->GetAnimInstance());

	movementComponent->StartFlyUp(1500.0f);
	animInst->StartFly();



	return EBTNodeResult::Type::InProgress;
}
