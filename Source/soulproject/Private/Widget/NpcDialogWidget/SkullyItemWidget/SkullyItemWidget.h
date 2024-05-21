// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "SkullyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class USkullyItemWidget : public UNpcDialogWidget
{
	GENERATED_BODY()
	

private:
	FTimerHandle SkullyItemShowTimerHandle;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void CreateWeaponWidget();

};
