// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupplyStoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class USupplyStoreWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_SupplyItem;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_SupplyItem;


public:
	UPROPERTY()
	TArray<class UButton*> SupplyItemButtons;

	void InitializeSupplyStoreWidget();

protected:
	virtual void NativeConstruct() override;


	
};
