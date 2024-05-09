#include "NiagaraSystem/AttackNiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"

UAttackNiagaraSystem::UAttackNiagaraSystem()
{
	// 나이아가라 컴포넌트 추가
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(
		TEXT("NiagaraComponent"));

	// 나이아가라 시스템 에셋 설정
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Lightning_Slash.NS_Lightning_Slash'"));

	if (NS_ATTACK.Succeeded())
		NiagaraComponent->SetAsset(NS_ATTACK.Object);

	// 공격한 위치를 저장합니다.
	//FVector attackLocation = GetAttackLocation();

	//NiagaraComponent->SetupAttachment(OwnerCharacter->GetMesh());

	//NiagaraComponent->SetWorldLocation(attackLocation);


	// 나이아가라 시스템을 활성화합니다.
	NiagaraComponent->ActivateSystem();

}

FVector UAttackNiagaraSystem::GetAttackLocation()
{
	AGamePlayerController* playerController = Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());
	OwnerCharacter = Cast<AGameCharacter>(playerController->GetPawn());

	if (!IsValidChecked(OwnerCharacter)) return FVector::ZeroVector;

	FVector location = OwnerCharacter->GetAttackComponent()->GetAttackLocation();
	return location;
}
