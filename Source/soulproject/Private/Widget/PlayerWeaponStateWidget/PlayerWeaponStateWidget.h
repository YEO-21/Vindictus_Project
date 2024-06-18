// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWeaponStateWidget.generated.h"

DECLARE_DELEGATE_OneParam(FUpdateTextureEventSignature, UTexture2D*)


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

	UPROPERTY(BlueprintReadWrite)
	bool IsExChangeWeapon;

	// 메인 무기 텍스쳐 
	UPROPERTY()
	UTexture2D* MainWeaponTexture;

public:
	FUpdateTextureEventSignature UpdateWeaponStateTexture;


protected:
	 virtual void NativeConstruct() override;

public:
	FUpdateTextureEventSignature GetWeaponStateEvent() const;

	void ExchangeWeaponWidget();

	UFUNCTION(BlueprintCallable)
	 bool GetExChangeWeaponState() const
	{
		return IsExChangeWeapon;
	}

	void HideWeaponStateWidget();
	void ShowWeaponStateWidget();

	void SetMainWeaponImage(UTexture2D* texture);
};
