// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWeaponStateWidget.generated.h"

#define PORTION_COUNT       3

/**
 * 
 */
UCLASS()
class UPlayerWeaponStateWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* MainWeapon;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_PortionCount;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ConsumeHp;

public:
	int32 PortionCount;


protected:
	 virtual void NativeConstruct() override;

public:
	void HideWeaponStateWidget();
	void ShowWeaponStateWidget();

	void SetMainWeaponImage(UTexture2D* texture);

	void ReducePortionCount();

	void SetPortionCount(int32 count);


	
};
