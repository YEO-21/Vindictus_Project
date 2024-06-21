// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/LevelTransition/LevelTransitionGameInstance/LevelTransitionGameInstance.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Object/InteractionParam/SupplyNpcInteractParam/SupplyNpcInteractParam.h"

#include "Widget/PlayerStateSlotWidget/PlayerStateSlotWidget.h"
#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"
#include "Widget/GameWidget/GameWidget.h"
#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"

#include "Structure/SupplyItemData/SupplyItemData.h"

#include"Component/PlayerBuffControlComponent/PlayerBuffControlComponent.h"
#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"



void ULevelTransitionGameInstance::SaveCharacterInfo(
	float hp, int32 remainPortionCount, FName equippedWeaponCode, TArray<FName> itemCodes)
{
	CurrentHp = hp;
	PortionCount = remainPortionCount;
	EquippedWeaponCode = equippedWeaponCode;
	BuffCodes = itemCodes;
}

void ULevelTransitionGameInstance::UpdateCharacterInfo(ACharacter* playerCharacter)
{
	AGameCharacter* player = Cast<AGameCharacter>(playerCharacter);
	AGamePlayerController* playerController = Cast<AGamePlayerController>(player->GetController());

	// ü�� �ε�
	playerController->SetCurrentHp(CurrentHp);
	
	
	// ���� �ڵ� �ε�
	player->EquippedWeaponCode = EquippedWeaponCode;
	player->GetEquipWeaponComponent()->EquipWeapon();
	player->isInteractable = false;


	
	// ���� Ƚ�� �ε�
	playerController->GetWeaponStateWidget()->SetPortionCount(PortionCount);



	// ���� �̹��� �ε�
	if (BuffCodes.Num() == 0) return;
	SetBuffImage(playerCharacter);
	


}

void ULevelTransitionGameInstance::Init()
{
	Super::Init();

	// ���� ���� �� ���� �ڵ�, ü���� �����մϴ�.
	EquippedWeaponCode = _SHARPNER;
	CurrentHp = 100.0f;
	PortionCount = PORTION_COUNT;


}

void ULevelTransitionGameInstance::SetBuffImage(ACharacter* playerCharacter)
{
	AGameCharacter* player = Cast<AGameCharacter>(playerCharacter);
	AGamePlayerController* playerController = Cast<AGamePlayerController>(player->GetController());


	USupplyStoreWidget* supplyWidget = playerController->GetSupplyStoreWidget();
	
	for (FName name : BuffCodes)
	{
		// �ڵ忡 �´� ���� ������ �ε�
		supplyWidget->InitializeItemCode(name);
		FSupplyItemData* supplyData = supplyWidget->PlayerSupplyData;

		UPlayerStateSlotWidget* slotWidget = playerController->GetPlayerStateSlotWidget();

		// ���� �̹��� �ε�
		slotWidget->SetImageMaterial(supplyData->ItemType, supplyData->BuffImage);
		playerController->GetGameWidget()->FloatingWidgetPlayerState(slotWidget);
		
		// ���� ȿ�� �ε�
		player->GetBuffControlComponent()->CheckCurrentBuff(supplyData->ItemType);

	}


}


