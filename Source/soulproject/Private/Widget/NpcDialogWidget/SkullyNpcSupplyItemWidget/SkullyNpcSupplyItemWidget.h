// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "SkullyNpcSupplyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class USkullyNpcSupplyItemWidget : public UNpcDialogWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay_Child;
private:
	FTimerHandle SupplyStoreShowTimerHandle;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void CreateSupplyItemWidget();
	
};
