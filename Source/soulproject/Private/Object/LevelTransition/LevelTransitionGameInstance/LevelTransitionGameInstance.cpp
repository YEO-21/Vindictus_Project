// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/LevelTransition/LevelTransitionGameInstance/LevelTransitionGameInstance.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"



void ULevelTransitionGameInstance::SaveCharacterInfo(float hp, float stamina, FName equippedWeaponCode)
{
	CurrentHp = hp;
	CurrentStamina = stamina;
	EquippedWeaponCode = equippedWeaponCode;
}

void ULevelTransitionGameInstance::UpdateCharacterInfo(ACharacter* playerCharacter)
{
	AGameCharacter* player = Cast<AGameCharacter>(playerCharacter);
	AGamePlayerController* playerController = Cast<AGamePlayerController>(player->GetController());

	// 체력 로드
	playerController->SetCurrentHp(CurrentHp);
	player->EquippedWeaponCode = EquippedWeaponCode;
	
	
	// 무기 코드 로드
	player->GetEquipWeaponComponent()->EquipWeapon();
	player->isInteractable = false;
	UE_LOG(LogTemp, Warning, TEXT("EquippedWeaponCode = %s"), *EquippedWeaponCode.ToString());

}

void ULevelTransitionGameInstance::Init()
{
	Super::Init();

	// 게임 시작 시 무기 코드, 체력을 설정합니다.
	EquippedWeaponCode = _SHARPNER;
	CurrentHp = 100.0f;


}


