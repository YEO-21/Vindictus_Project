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
	// ���� ������ ���� �ڵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	FName EquippedWeaponCode;

	// ���� ���� �ڵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	TArray<FName> BuffCodes;


	// ���� ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	float CurrentHp;

	// ���� ��� Ƚ�� 
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
