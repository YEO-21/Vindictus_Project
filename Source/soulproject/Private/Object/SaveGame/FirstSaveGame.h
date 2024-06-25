// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FirstSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UFirstSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	// 현재 무기 타입  코드
	UPROPERTY()
	FName CurrentWeaponCode;

	// 현재 장착된 무기 코드
	UPROPERTY()
	FName EquippedWeaponCode;
	

	// 현재 버프
	UPROPERTY()
	TArray<class USupplyNpcInteractParam*> Buff;

	// 현재 체력
	UPROPERTY()
	float CurrentHp;

	// 현재 스테미너
	UPROPERTY()
	float CurrentStamina;


	
public:
	UFirstSaveGame();




};
