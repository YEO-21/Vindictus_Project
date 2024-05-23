// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTabel.h"
#include "SupplyItemData.generated.h"

USTRUCT()
struct FSupplyItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


public:
	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BuffName;

	// ���� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture BuffImage;

	// ���� �ɷ�
	class USupplyNpcInteractParam* BuffObject;



};
