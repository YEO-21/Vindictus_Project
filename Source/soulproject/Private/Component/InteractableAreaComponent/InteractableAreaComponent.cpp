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

	// 교환이 가능한지 확인합니다.
	bool exchangeWeapon = Cast<ANpcCharacter>(GetOwner())->GetIsFullfill();

	// 교환이 가능하면 플레이어의 장착 무기 코드를 설정합니다.
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

		// 상호작용 컴포넌트를 얻습니다.
		PlayerCharacter->GetInteractComponent()->AddInteractableArea(this);

		// 교환이 가능한지 확인합니다.
		bool exchangeWeapon = Cast<ANpcCharacter>(GetOwner())->GetIsFullfill();

		// 교환이 가능하면 플레이어의 장착 무기 코드를 설정합니다.
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

		// 상호작용 컴포넌트를 얻습니다.
		gameCharacter->GetInteractComponent()->RemoveInteractableArea(this);

	}

}
