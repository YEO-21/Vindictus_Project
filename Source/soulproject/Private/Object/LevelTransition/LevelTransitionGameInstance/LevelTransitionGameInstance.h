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
	// ���� ���� Ÿ��  �ڵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	FName CurrentWeaponCode;

	// ���� ������ ���� �ڵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	FName EquippedWeaponCode;


	// ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	TArray<class USupplyNpcInteractParam*> Buff;

	// ���� ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameSetting")
	float CurrentHp;

	// ���� ���׹̳�
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
