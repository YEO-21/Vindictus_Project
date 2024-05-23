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
	// 버프 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BuffName;

	// 버프 이미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture BuffImage;

	// 버프 능력
	class USupplyNpcInteractParam* BuffObject;



};
