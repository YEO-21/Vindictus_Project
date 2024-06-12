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
	// ���� ���� Ÿ��  �ڵ�
	UPROPERTY()
	FName CurrentWeaponCode;

	// ���� ������ ���� �ڵ�
	UPROPERTY()
	FName EquippedWeaponCode;
	

	// ���� ����
	UPROPERTY()
	TArray<class USupplyNpcInteractParam*> Buff;

	// ���� ü��
	UPROPERTY()
	float CurrentHp;

	// ���� ���׹̳�
	UPROPERTY()
	float CurrentStamina;


	
public:
	UFirstSaveGame();




};
