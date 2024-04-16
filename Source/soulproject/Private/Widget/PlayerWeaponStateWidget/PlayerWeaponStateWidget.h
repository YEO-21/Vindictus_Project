// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWeaponStateWidget.generated.h"

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
	class UImage* SubWeapon;


protected:
	 virtual void NativeConstruct() override;

public:
	void ExchangeWeaponWidget();

};
