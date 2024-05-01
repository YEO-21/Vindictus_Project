// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
DECLARE_EVENT(UWeaponStoreWidget, PassWeaponWidgetSignature)
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
	PassWeaponWidgetSignature PassWeaponWidget;
	GetItemNameSignature GetItemName;

	UPROPERTY()
	class UUniformGridPanel* ItemGridPanel;

	UPROPERTY()
	bool isTradable;
	
	
public:
	UWeaponStoreWidget(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeConstruct() override;

public:
	void InitializeWeaponStoreWidget(TArray<FName> itemCodes);
	void InitializeItemNameWidget(GetItemNameSignature itemName);
	void InitializePassItemNameWidget(PassWeaponWidgetSignature passWeaponWidget);

	UFUNCTION()
	void OnBuyButtonClicked();


};
