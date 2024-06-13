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
	player->SetCurrentHp(CurrentHp);
	player->EquippedWeaponCode = EquippedWeaponCode;
	
	player->GetEquipWeaponComponent()->EquipWeapon();
	player->isInteractable = false;
	UE_LOG(LogTemp, Warning, TEXT("EquippedWeaponCode = %s"), *EquippedWeaponCode.ToString());

}

void ULevelTransitionGameInstance::Init()
{
	Super::Init();

	EquippedWeaponCode = _SHARPNER;

}


