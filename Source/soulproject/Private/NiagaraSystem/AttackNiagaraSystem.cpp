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
	

	// 나이아가라 컴포넌트 추가
	NiagaraComponent =
		CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));


	// 나이아가라 피격 컴포넌트 추가
	HitNiagaraComponent = 
		CreateDefaultSubobject<UNiagaraComponent>(TEXT("HitNiagaraComponent"));

	// 나이아가라 치명타 컴포넌트 추가
	CriticalAttackNiagaraComponent =
		CreateDefaultSubobject<UNiagaraComponent>(TEXT("CriticalAttackNiagaraComponent"));

	
	NiagaraComponent->ActivateSystem();
	HitNiagaraComponent->ActivateSystem();

	// 나이아가라 시스템 에셋 설정
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Lightning_Slash.NS_Lightning_Slash'"));
	
	// 나이아가라 시스템 피격 에셋 설정
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACKHIT(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Impacts/NS_Lightning_Slash_Impact.NS_Lightning_Slash_Impact'"));

	// 치명타 나이아가라 시스템 에셋 설정
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_CRITICALATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Claws_Floor.NS_Claws_Floor'"));

	if (NS_ATTACK.Succeeded())
		NiagaraComponent->SetAsset(NS_ATTACK.Object);

	if (NS_ATTACKHIT.Succeeded())
		HitNiagaraComponent->SetAsset(NS_ATTACKHIT.Object);

	if (NS_CRITICALATTACK.Succeeded())
		CriticalAttackNiagaraComponent->SetAsset(NS_CRITICALATTACK.Object);

	// 나이아가라 시스템 크기 설정
	NiagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	CriticalAttackNiagaraComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	// 나이아가라 시스템 자동 활성화 on
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
	// 나이아가라 시스템 활성화 
	NiagaraComponent->ActivateSystem();
	HitNiagaraComponent->ActivateSystem();

	NiagaraComponent->Activate();
	HitNiagaraComponent->Activate();

	
}

void UAttackNiagaraSystem::SetNiagaraSystemLocation(FVector playerlocation, FVector hitLocation)
{
	// 나이아가라 시스템 월드 위치 설정
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


	// 나이아가라 시스템 에셋 설정
	NiagaraComponent->SetAsset(effect);
	HitNiagaraComponent->SetAsset(hiteffect);

	// 나이아가라 시스템 비활성화
	NiagaraComponent->Deactivate();
	HitNiagaraComponent->Deactivate();

}
