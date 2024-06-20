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
	// 현재 장착된 무기 코드
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	FName EquippedWeaponCode;

	// 현재 버프 코드
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	TArray<FName> BuffCodes;


	// 현재 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	float CurrentHp;

	// 포션 사용 횟수 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	int32 PortionCount;



public:
	UFUNCTION(BlueprintCallable)
	void SaveCharacterInfo(float hp, int32 remainPortionCount, FName WeaponCode, TArray<FName> itemcodes);

	UFUNCTION(BlueprintCallable)
	void UpdateCharacterInfo(class ACharacter* playerCharacter);



protected:
	virtual void Init() override;

	void SetBuffImage(ACharacter* playerCharacter);
};
