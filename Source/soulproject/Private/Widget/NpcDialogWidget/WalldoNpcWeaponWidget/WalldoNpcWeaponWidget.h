// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "WalldoNpcWeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class UWalldoNpcWeaponWidget : public UNpcDialogWidget
{
	GENERATED_BODY()


private:
	FTimerHandle WeaponStoreShowTimerHandle;


protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void CreateWeaponWidget();

private:
	void HideDialogGameWidget();
	
	
};
