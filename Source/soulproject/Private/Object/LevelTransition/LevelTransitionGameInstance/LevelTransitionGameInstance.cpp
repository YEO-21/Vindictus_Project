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

	// 체력 로드
	playerController->SetCurrentHp(CurrentHp);
	
	
	// 무기 코드 로드
	player->EquippedWeaponCode = EquippedWeaponCode;
	player->GetEquipWeaponComponent()->EquipWeapon();
	player->isInteractable = false;


	
	// 포션 횟수 로드
	playerController->GetWeaponStateWidget()->SetPortionCount(PortionCount);



	// 버프 이미지 로드
	if (BuffCodes.Num() == 0) return;
	SetBuffImage(playerCharacter);
	


}

void ULevelTransitionGameInstance::Init()
{
	Super::Init();

	// 게임 시작 시 무기 코드, 체력을 설정합니다.
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
		// 코드에 맞는 버프 데이터 로드
		supplyWidget->InitializeItemCode(name);
		FSupplyItemData* supplyData = supplyWidget->PlayerSupplyData;

		UPlayerStateSlotWidget* slotWidget = playerController->GetPlayerStateSlotWidget();

		// 버프 이미지 로드
		slotWidget->SetImageMaterial(supplyData->ItemType, supplyData->BuffImage);
		playerController->GetGameWidget()->FloatingWidgetPlayerState(slotWidget);
		
		// 버프 효과 로드
		player->GetBuffControlComponent()->CheckCurrentBuff(supplyData->ItemType);

	}


}


