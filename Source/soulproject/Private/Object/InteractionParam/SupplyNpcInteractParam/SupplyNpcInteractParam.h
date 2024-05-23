// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY()
	USupplyNpcInteractParam* AttackSupply;
	
	UPROPERTY()
	USupplyNpcInteractParam* DefenceSupply;

	UPROPERTY()
	USupplyNpcInteractParam* HpSupply;

	UPROPERTY()
	USupplyNpcInteractParam* CriticalAttackSupply;
	



};
