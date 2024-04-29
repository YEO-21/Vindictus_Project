#include "Component/InteractableAreaComponent/InteractableAreaComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/NpcCharacter/NpcCharacter.h"
#include "Component/PlayerCharacterInteractComponent/PlayerCharacterInteractComponent.h"

UInteractableAreaComponent::UInteractableAreaComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UInteractableAreaComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractableAreaComponent::OnEndOverlap);

}

bool UInteractableAreaComponent::StartInteraction(FOnInteractionFinishEventSignature onInteractionFinished)
{
	return Cast<ANpcCharacter>(GetOwner())->OnInteractionStarted(onInteractionFinished);
}

void UInteractableAreaComponent::SetIsFullFill()
{
	// ���� ��ȯ �������� �����մϴ�.
	Cast<ANpcCharacter>(GetOwner())->SetIsFullfill(true);
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
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(OtherActor);

		// ��ȣ�ۿ� ������Ʈ�� ����ϴ�.
		gameCharacter->GetInteractComponent()->AddInteractableArea(this);

		// ���� ��ȯ �������� �����մϴ�.
		//SetIsFullFill();

		// ��ȯ�� �������� Ȯ���մϴ�.
		bool exchangeWeapon = Cast<ANpcCharacter>(GetOwner())->GetIsFullfill();

		// ��ȯ�� �����ϸ� �÷��̾��� ���� ���� �ڵ带 �����մϴ�.
		if (exchangeWeapon) gameCharacter->EquippedWeaponCode = TEXT("000003");

		UE_LOG(LogTemp, Warning, TEXT("EquippedWeaponCode is %s"), *gameCharacter->EquippedWeaponCode.ToString());
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
