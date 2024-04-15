#include "Component/WolfAttackComponent/WolfAttackComponent.h"

#include "Actor/EnemyCharacter/Wolf/WolfCharacter.h"

UWolfAttackComponent::UWolfAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_ATTACK(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/AnimalVarietyPack/Wolf/Animations/AnimMontage_Attack.AnimMontage_Attack'"));
	if (ANIMMONTAGE_ATTACK.Succeeded())
	{
		AttackAnimMontage = ANIMMONTAGE_ATTACK.Object;
	}

}

void UWolfAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWolfAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWolfAttackComponent::Attack()
{
	Cast<AWolfCharacter>(GetOwner())->PlayAnimMontage(AttackAnimMontage);
}

