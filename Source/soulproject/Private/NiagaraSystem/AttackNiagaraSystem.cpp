#include "NiagaraSystem/AttackNiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraScript.h"
#include "NiagaraScriptBase.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"

UAttackNiagaraSystem::UAttackNiagaraSystem()
{
	

	// ���̾ư��� ������Ʈ �߰�
	NiagaraComponent =
		CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));


	// ���̾ư��� �ǰ� ������Ʈ �߰�
	HitNiagaraComponent = 
		CreateDefaultSubobject<UNiagaraComponent>(TEXT("HitNiagaraComponent"));

	// ���̾ư��� ġ��Ÿ ������Ʈ �߰�
	CriticalAttackNiagaraComponent =
		CreateDefaultSubobject<UNiagaraComponent>(TEXT("CriticalAttackNiagaraComponent"));

	
	NiagaraComponent->ActivateSystem();
	HitNiagaraComponent->ActivateSystem();

	// ���̾ư��� �ý��� ���� ����
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Lightning_Slash.NS_Lightning_Slash'"));
	
	// ���̾ư��� �ý��� �ǰ� ���� ����
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACKHIT(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Impacts/NS_Lightning_Slash_Impact.NS_Lightning_Slash_Impact'"));

	// ġ��Ÿ ���̾ư��� �ý��� ���� ����
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_CRITICALATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Claws_Floor.NS_Claws_Floor'"));

	if (NS_ATTACK.Succeeded())
		NiagaraComponent->SetAsset(NS_ATTACK.Object);

	if (NS_ATTACKHIT.Succeeded())
		HitNiagaraComponent->SetAsset(NS_ATTACKHIT.Object);

	if (NS_CRITICALATTACK.Succeeded())
		CriticalAttackNiagaraComponent->SetAsset(NS_CRITICALATTACK.Object);

	// ���̾ư��� �ý��� ũ�� ����
	NiagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	CriticalAttackNiagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	// ���̾ư��� �ý��� �ڵ� Ȱ��ȭ on
	NiagaraComponent->bAutoActivate = true;
	HitNiagaraComponent->bAutoActivate = true;

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
	// ���̾ư��� �ý��� Ȱ��ȭ 
	NiagaraComponent->ActivateSystem();
	HitNiagaraComponent->ActivateSystem();

	NiagaraComponent->Activate();
	HitNiagaraComponent->Activate();

	
}

void UAttackNiagaraSystem::SetNiagaraSystemLocation(FVector playerlocation, FVector hitLocation)
{
	// ���̾ư��� �ý��� ���� ��ġ ����
	NiagaraComponent->SetWorldLocation(playerlocation);
	HitNiagaraComponent->SetWorldLocation(hitLocation);
}

void UAttackNiagaraSystem::SetCriticalNiagaraSystemLocation(FVector hitLocation)
{
	CriticalAttackNiagaraComponent->ActivateSystem();
	CriticalAttackNiagaraComponent->Activate();

	CriticalAttackNiagaraComponent->SetWorldLocation(hitLocation);

}

void UAttackNiagaraSystem::SetNiagaraSystemAsset(UNiagaraSystem* effect, UNiagaraSystem* hiteffect)
{
	if (effect == nullptr) return;
	if (hiteffect == nullptr) return;


	// ���̾ư��� �ý��� ���� ����
	NiagaraComponent->SetAsset(effect);
	HitNiagaraComponent->SetAsset(hiteffect);

	// ���̾ư��� �ý��� ��Ȱ��ȭ
	NiagaraComponent->Deactivate();
	HitNiagaraComponent->Deactivate();

}
