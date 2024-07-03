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
	// 상호작용 가능한 영역을 나간 후 처음 발견되는 경우
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
	// 상호 작용 가능한 객체가 존재하지 않을 경우
	if (InteractableAreas.Num() < 1) return;

	// Get GameCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());


	FOnInteractionFinishEventSignature onInteractionFinished;
	onInteractionFinished.AddUObject(this, &UPlayerCharacterInteractComponent::OnInteractionFinished);

	// 첫 번째 상호작용 영역 컴포넌트를 얻습니다.
	UInteractableAreaComponent* interactableArea = InteractableAreas[0];

	NewObject<UObject>(this, TEXT("NpcWeaponBase"), EObjectFlags::RF_Dynamic);
	
	

	// 상호작용 성공 여부를 얻습니다.
	bool isSucceeded = interactableArea->StartInteraction(onInteractionFinished);

	if (isSucceeded)
	{
		// 상호작용 시간 기록
		InteractTime = GetWorld()->GetTimeSeconds();

		// 상호작용 대상(NPC)
		ANpcCharacter* npc = Cast<ANpcCharacter>(interactableArea->GetOwner());


		// 상호작용 시작
		OnInteractionStarted(
			npc->GetInteractionLocation(),
			npc->GetInteractionRotation());

		// 상호작용 카메라 타겟을 Npc로 설정
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

	// 이동 입력을 막습니다.
	playerCharacter->GetPlayerCharacterMovementComponent()->SetAllowMovementInput(false);

	// 이전 위치 저장
	BeforeInteractionLocation = playerCharacter->GetMesh()->GetRelativeLocation();
	BeforeInteractionRotation = playerCharacter->GetMesh()->GetRelativeRotation();

	// 상호작용 위치, 회전 설정
	playerCharacter->GetMesh()->SetWorldLocation(interactionLocation);
	playerCharacter->GetMesh()->SetWorldRotation(interactionRotation);
}

void UPlayerCharacterInteractComponent::OnInteractionFinished()
{
	// Get GameCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	// 이동 입력 허용
	playerCharacter->GetPlayerCharacterMovementComponent()->SetAllowMovementInput(true);

	// 상호작용 위치, 회전 되돌리기
	playerCharacter->GetMesh()->SetRelativeLocation(BeforeInteractionLocation);
	playerCharacter->GetMesh()->SetRelativeRotation(BeforeInteractionRotation);

	Cast<AGamePlayerController>(playerCharacter->GetController())->ClearCameraViewTarget();


}

void UPlayerCharacterInteractComponent::RequestWeaponChange()
{
	ANpcCharacter* npc = Cast<ANpcCharacter>(InteractableAreas[0]->GetOwner());
	npc->SetIsFullfill(true);
}

