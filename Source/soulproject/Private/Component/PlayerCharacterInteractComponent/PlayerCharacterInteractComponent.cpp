#include "Component/PlayerCharacterInteractComponent/PlayerCharacterInteractComponent.h"
#include "Component/InteractableAreaComponent/InteractableAreaComponent.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"
#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"
#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/NpcCharacter/NpcCharacter.h"

#include "Object/InteractionParam/InteractionParamBase.h"
#include "Object/InteractionParam/WeaponNpcInteractParam/WeaponNpcInteractParam.h"

UPlayerCharacterInteractComponent::UPlayerCharacterInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacterInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPlayerCharacterInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerCharacterInteractComponent::AddInteractableArea(UInteractableAreaComponent* newArea)
{
	// ��ȣ�ۿ� ������ ������ ���� �� ó�� �߰ߵǴ� ���
	if (!InteractableAreas.Contains(newArea))
		InteractableAreas.Add(newArea);
}

void UPlayerCharacterInteractComponent::RemoveInteractableArea(UInteractableAreaComponent* newArea)
{
	if (InteractableAreas.Contains(newArea))
		InteractableAreas.Remove(newArea);

}

void UPlayerCharacterInteractComponent::TryInteraction()
{
	// ��ȣ �ۿ� ������ ��ü�� �������� ���� ���
	if (InteractableAreas.Num() < 1) return;

	// Get GameCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());


	FOnInteractionFinishEventSignature onInteractionFinished;
	onInteractionFinished.AddUObject(this, &UPlayerCharacterInteractComponent::OnInteractionFinished);

	// ù ��° ��ȣ�ۿ� ���� ������Ʈ�� ����ϴ�.
	UInteractableAreaComponent* interactableArea = InteractableAreas[0];

	NewObject<UObject>(this, TEXT("NpcWeaponBase"), EObjectFlags::RF_Dynamic);
	
	

	// ��ȣ�ۿ� ���� ���θ� ����ϴ�.
	bool isSucceeded = interactableArea->StartInteraction(onInteractionFinished);

	if (isSucceeded)
	{
		// ��ȣ�ۿ� �ð� ���
		InteractTime = GetWorld()->GetTimeSeconds();

		// ��ȣ�ۿ� ���(NPC)
		ANpcCharacter* npc = Cast<ANpcCharacter>(interactableArea->GetOwner());


		// ��ȣ�ۿ� ����
		OnInteractionStarted(
			npc->GetInteractionLocation(),
			npc->GetInteractionRotation());

		// ��ȣ�ۿ� ī�޶� Ÿ���� Npc�� ����
		Cast<AGamePlayerController>(playerCharacter->GetController())->SetCameraViewTarget(npc);


		NewObject<UObject>(this, TEXT("NpcWeaponBase"), EObjectFlags::RF_Dynamic);
		 if (npc->GetNpcType() == ENpcType::WeaponBase)
		 {
			 UWeaponNpcInteractParam* weaponNpcInteractParam = 
				 NewObject<UWeaponNpcInteractParam>(this);
		 }
	
	}
}

void UPlayerCharacterInteractComponent::OnInteractionStarted(
	FVector interactionLocation, FRotator interactionRotation)
{
	// Get GameCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	// �̵� �Է��� �����ϴ�.
	playerCharacter->GetPlayerCharacterMovementComponent()->SetAllowMovementInput(false);

	// ���� ��ġ ����
	BeforeInteractionLocation = playerCharacter->GetMesh()->GetRelativeLocation();
	BeforeInteractionRotation = playerCharacter->GetMesh()->GetRelativeRotation();

	// ��ȣ�ۿ� ��ġ, ȸ�� ����
	playerCharacter->GetMesh()->SetWorldLocation(interactionLocation);
	playerCharacter->GetMesh()->SetWorldRotation(interactionRotation);
}

void UPlayerCharacterInteractComponent::OnInteractionFinished()
{
	// Get GameCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	// �̵� �Է� ���
	playerCharacter->GetPlayerCharacterMovementComponent()->SetAllowMovementInput(true);

	// ��ȣ�ۿ� ��ġ, ȸ�� �ǵ�����
	playerCharacter->GetMesh()->SetRelativeLocation(BeforeInteractionLocation);
	playerCharacter->GetMesh()->SetRelativeRotation(BeforeInteractionRotation);

	Cast<AGamePlayerController>(playerCharacter->GetController())->ClearCameraViewTarget();


}

void UPlayerCharacterInteractComponent::RequestWeaponChange()
{
	ANpcCharacter* npc = Cast<ANpcCharacter>(InteractableAreas[0]->GetOwner());
	npc->SetIsFullfill(true);
}

