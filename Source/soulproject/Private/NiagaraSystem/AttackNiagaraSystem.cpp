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

	// ���̾ư��� �ý��� ���� ����
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ATTACK(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Slashes/NS_Lightning_Slash.NS_Lightning_Slash'"));

	if (NS_ATTACK.Succeeded())
		NiagaraComponent->SetAsset(NS_ATTACK.Object);

	// ������ ��ġ�� �����մϴ�.
	//FVector attackLocation = GetAttackLocation();

	//NiagaraComponent->SetupAttachment(OwnerCharacter->GetMesh());

	//NiagaraComponent->SetWorldLocation(attackLocation);


	// ���̾ư��� �ý����� Ȱ��ȭ�մϴ�.
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
