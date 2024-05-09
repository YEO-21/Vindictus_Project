#include "NiagaraSystem/AttackNiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"

UAttackNiagaraSystem::UAttackNiagaraSystem()
{
	// ���̾ư��� ������Ʈ �߰�
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(
		TEXT("NiagaraComponent"));

	// ���̾ư��� �ǰ� ������Ʈ �߰�
	HitNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(
		TEXT("HitNiagaraComponent"));


	// ���̾ư��� �ý��� ���� ����
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Lightning_Slash.NS_Lightning_Slash'"));
	
	// ���̾ư��� �ý��� �ǰ� ���� ����
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACKHIT(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Impacts/NS_Lightning_Slash_Impact.NS_Lightning_Slash_Impact'"));

	if (NS_ATTACK.Succeeded())
		NiagaraComponent->SetAsset(NS_ATTACK.Object);

	if (NS_ATTACKHIT.Succeeded())
		HitNiagaraComponent->SetAsset(NS_ATTACKHIT.Object);

	NiagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));


	// ������ ��ġ�� �����մϴ�.
	//FVector attackLocation = GetAttackLocation();

	//NiagaraComponent->SetupAttachment(OwnerCharacter->GetMesh());

	//NiagaraComponent->SetWorldLocation(attackLocation);

	//NiagaraComponent->SetWorldLocation();

}

FVector UAttackNiagaraSystem::GetAttackLocation()
{
	AGamePlayerController* playerController = Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());
	OwnerCharacter = Cast<AGameCharacter>(playerController->GetPawn());

	if (!IsValidChecked(OwnerCharacter)) return FVector::ZeroVector;

	FVector location = OwnerCharacter->GetAttackComponent()->GetAttackLocation();
	return location;
}

void UAttackNiagaraSystem::ActivateNiagaraSystem()
{
	NiagaraComponent->ActivateSystem();
	HitNiagaraComponent->ActivateSystem();
}

void UAttackNiagaraSystem::SetNiagaraSystemLocation(FVector playerlocation, FVector hitLocation)
{
	NiagaraComponent->SetWorldLocation(playerlocation);
	NiagaraComponent->SetWorldLocation(hitLocation);
}

void UAttackNiagaraSystem::SetNiagaraSystemAsset(UNiagaraSystem* effect, UNiagaraSystem* hiteffect)
{
	NiagaraComponent->SetAsset(effect);
	HitNiagaraComponent->SetAsset(hiteffect);

}
