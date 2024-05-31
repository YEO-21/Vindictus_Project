// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/SupplyItem/SupplyItemType.h"
#include "Engine/DataTable.h"
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
	UMaterialInterface* BuffImage;

	// 가격
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BuffPrice;
		
	// 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PersistTime;

	// 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESupplyItemType ItemType;

	// 아이템 효과
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemEffect;

public:
	FSupplyItemData();
	

};
