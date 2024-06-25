// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/SupplyItem/SupplyItemType.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerStateSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Slot_Atk;

	UPROPERTY(meta = (BindWidget))
	class UImage* Slot_Def;

	UPROPERTY(meta = (BindWidget))
	class UImage* Slot_Hp;

	UPROPERTY(meta = (BindWidget))
	class UImage* Slot_Critical;

public:
	bool bIsActivated;

	TArray<class UImage*> Images;

protected:
	virtual void NativeConstruct() override;

public:
	void SetImageMaterial(ESupplyItemType itemType, UMaterialInterface* material);
	
};
