// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/InteractionParam/InteractionParamBase.h"
#include "ComsumeNpcInteractParam.generated.h"

/**
 * 
 */
UCLASS()
class UComsumeNpcInteractParam : public UInteractionParamBase
{
	GENERATED_BODY()
	
public:
	// �Ǹ� ������ ���
	TArray<FName> SaleItemCodes;

	TSubclassOf<class USkullyItemWidget> BP_SkullyItemWidgetClass;

};
