// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LevelTransitionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ULevelTransitionGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// 현재 무기 타입  코드
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	FName CurrentWeaponCode;

	// 현재 장착된 무기 코드
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	FName EquippedWeaponCode;


	// 현재 버프
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	TArray<class USupplyNpcInteractParam*> Buff;

	// 현재 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	float CurrentHp;

	// 현재 스테미너
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	float CurrentStamina;

public:
	UFUNCTION(BlueprintCallable)
	void SaveCharacterInfo(float hp, float stamina, FName WeaponCode);

	UFUNCTION(BlueprintCallable)
	void UpdateCharacterInfo(class ACharacter* playerCharacter);



protected:
	virtual void Init() override;
};
