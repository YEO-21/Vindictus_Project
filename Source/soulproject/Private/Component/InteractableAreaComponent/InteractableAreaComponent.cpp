#include "Component/InteractableAreaComponent/InteractableAreaComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/NpcCharacter/NpcCharacter.h"
#include "Component/PlayerCharacterInteractComponent/PlayerCharacterInteractComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"

UInteractableAreaComponent::UInteractableAreaComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UInteractableAreaComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractableAreaComponent::OnEndOverlap);

}

bool UInteractableAreaComponent::StartInteraction(FOnInteractionFinishEventSignature onInteractionFinished)
{
	return Cast<ANpcCharacter>(GetOwner())->OnInteractionStarted(onInteractionFinished);
}

void UInteractableAreaComponent::SetTradable(FName equipItemCode)
{

	// ��ȯ�� �������� Ȯ���մϴ�.
	bool exchangeWeapon = Cast<ANpcCharacter>(GetOwner())->GetIsFullfill();

	// ��ȯ�� �����ϸ� �÷��̾��� ���� ���� �ڵ带 �����մϴ�.
	if (exchangeWeapon) PlayerCharacter->EquippedWeaponCode = equipItemCode;//TEXT("000003");

	PlayerCharacter->GetEquipWeaponComponent()->InitializeEquippedWeapon();
	PlayerCharacter->GetEquipWeaponComponent()->EquipWeapon();
	UE_LOG(LogTemp, Warning, TEXT("SetTradable is Called"));
}



void UInteractableAreaComponent::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AGameCharacter>())
	{
		PlayerCharacter = Cast<AGameCharacter>(OtherActor);

		// ��ȣ�ۿ� ������Ʈ�� ����ϴ�.
		PlayerCharacter->GetInteractComponent()->AddInteractableArea(this);

		// ��ȯ�� �������� Ȯ���մϴ�.
		bool exchangeWeapon = Cast<ANpcCharacter>(GetOwner())->GetIsFullfill();

		// ��ȯ�� �����ϸ� �÷��̾��� ���� ���� �ڵ带 �����մϴ�.
		if (exchangeWeapon) PlayerCharacter->EquippedWeaponCode = TEXT("000003");

		UE_LOG(LogTemp, Warning, TEXT("EquippedWeaponCode is %s"), *PlayerCharacter->EquippedWeaponCode.ToString());
	}
}

void UInteractableAreaComponent::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AGameCharacter>())
	{
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(OtherActor);

		// ��ȣ�ۿ� ������Ʈ�� ����ϴ�.
		gameCharacter->GetInteractComponent()->RemoveInteractableArea(this);

	}

}
