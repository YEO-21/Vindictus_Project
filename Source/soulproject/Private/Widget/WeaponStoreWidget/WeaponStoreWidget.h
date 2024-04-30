// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_EVENT_OneParam(UWeaponStoreWidget, WeaponBuyButtonClickSignature, FName /*equipItemCode*/)
DECLARE_DELEGATE_RetVal(FName, GetItemNameSignature)

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

	TSubclassOf<class UStoreItemWidget> WidgetBP_StoreItemClass;

public:
	WeaponBuyButtonClickSignature WeaponBuyEvent;
	GetItemNameSignature GetItemName;

	UPROPERTY()
	class UUniformGridPanel* ItemGridPanel;

	UPROPERTY()
	bool isTradable;
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Weapon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Buy;

	//UPROPERTY()
	//TArray<class UButton*> Buttons;
	//TMap<class UButton* /*Button Instance*/, FName /*Item Code*/> BuyButtons;

	
public:
	UWeaponStoreWidget(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeConstruct() override;

public:
	void InitializeWeaponStoreWidget(WeaponBuyButtonClickSignature weaponStoreWidgetEvent);
	void InitializeWeaponStoreWidget(TArray<FName> itemCodes);
	void InitializeItemNameWidget(GetItemNameSignature itemName);

private:
	UFUNCTION()
	void OnButtonBuyClicked();




};
