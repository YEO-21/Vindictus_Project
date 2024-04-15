#include "AI/Task/Dragon/BTTask_Falling.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Component/DragonCharacterMovementComponent/DragonCharacterMovementComponent.h"
#include"AnimInstance/DragonCharacter/DragonCharacterAnimInstance.h"

UBTTask_Falling::UBTTask_Falling()
{
	TargetActorKey.AddObjectFilter(this, 
		GET_MEMBER_NAME_CHECKED(ThisClass, TargetActorKey),
		UObject::StaticClass());

	bNotifyTick = true;
}

void UBTTask_Falling::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float dt)
{
	Super::TickTask(ownerComp, nodeMemory, dt);

	ADragonCharacter* dragonCharacter = Cast<ADragonCharacter>(Cast<AController>(ownerComp.GetOwner())->GetPawn());


	UDragonCharacterMovementComponent* movementComponent = 
		dragonCharacter->GetDragonMovementComponent();

	UDragonCharacterAnimInstance* animInst = Cast<UDragonCharacterAnimInstance>(dragonCharacter->GetMesh()->GetAnimInstance());


	if (!movementComponent->GetFlyState())
	{
		animInst->FinishFlying();
		FinishLatentTask(ownerComp, EBTNodeResult::Type::Succeeded);
	}

}

EBTNodeResult::Type UBTTask_Falling::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	ADragonCharacter* dragonCharacter = 
		Cast<ADragonCharacter>(Cast<AController>(ownerComponent.GetOwner())->GetPawn());


	UDragonCharacterMovementComponent* movementComponent = 
		dragonCharacter->GetDragonMovementComponent();

	UDragonCharacterAnimInstance* animInst = 
		Cast<UDragonCharacterAnimInstance>(dragonCharacter->GetMesh()->GetAnimInstance());

	animInst->StartFalling();
	movementComponent->StartFalling();


	return EBTNodeResult::Type::InProgress;
}
