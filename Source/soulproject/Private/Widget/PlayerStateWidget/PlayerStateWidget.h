// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	class UProgressBar * Progressbar_Hp;

	UPROPERTY()
	class UProgressBar * Progressbar_Stamina;

private :
	// 최대 체력
	float MaxHp;
	
	// 현재 체력
	float CurrentHp;

	// 최대 스테미너
	float MaxStamina;

	// 현재 스테미너
	float CurrentStamina;



protected :
	virtual void NativeConstruct() override;

private :
	UFUNCTION()
	float GetHpPercent() const;

	UFUNCTION()
	float GetStaminaPercent() const;

public :
	FORCEINLINE void SetMaxHp(float maxHp) { MaxHp = maxHp; }
	FORCEINLINE void SetMaxStamina(float maxStamina) { MaxStamina = maxStamina; }

	FORCEINLINE void UpdateHp(float currentHp) { CurrentHp = currentHp; }
	FORCEINLINE void UpdateStamina(float currentStamina) { CurrentStamina = currentStamina; }

};
