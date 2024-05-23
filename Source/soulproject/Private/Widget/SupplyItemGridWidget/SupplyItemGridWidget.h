// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupplyItemGridWidget.generated.h"

/**
 * 
 */
UCLASS()
class USupplyItemGridWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGridPanel;

protected:
	virtual void NativeConstruct() override;
	
public:
	void InitializeSupplyStoreWidget();


};
