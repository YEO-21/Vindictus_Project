// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/SupplyItem/SupplyItemType.h"
#include "Object/InteractionParam/InteractionParamBase.h"
#include "SupplyNpcInteractParam.generated.h"

/**
 * 
 */
UCLASS()
class USupplyNpcInteractParam : public UInteractionParamBase
{
	GENERATED_BODY()

public:
	TSubclassOf<class USupplyStoreWidget> BP_SupplyStoreWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsEnable;
	
	// 아이템 타입
	ESupplyItemType ItemType;

	// 아이템 활성화 이미지
	UMaterialInterface* ItemImage;


	
	

public:
	


};
