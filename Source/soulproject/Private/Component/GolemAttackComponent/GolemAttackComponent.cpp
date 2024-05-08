#include "Component/GolemAttackComponent/GolemAttackComponent.h"

#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"

UGolemAttackComponent::UGolemAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GOLEMATTACK_ANIMMONTAGE(
		TEXT("/Script/Engine.AnimMontage'/Game/Ancient_Golem/Animation/AnimMontage_GolemAttack.AnimMontage_GolemAttack'"));

	if (GOLEMATTACK_ANIMMONTAGE.Succeeded())
		AttackAnimMontage = GOLEMATTACK_ANIMMONTAGE.Object;


}


void UGolemAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UGolemAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGolemAttackComponent::Attack(FName sectionName)
{
	// ���� �ִ� ��Ÿ�� ����մϴ�.
	Cast<AGolemCharacter>(GetOwner())->PlayAnimMontage(AttackAnimMontage, 1.0f, sectionName);

}

