// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_EVENT(UWeaponStoreWidget, WeaponBuyButtonClickSignature)

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponStoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class UWeaponStoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	WeaponBuyButtonClickSignature WeaponBuyEvent;
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Weapon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Buy;


protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnButtonBuyClicked();

};
