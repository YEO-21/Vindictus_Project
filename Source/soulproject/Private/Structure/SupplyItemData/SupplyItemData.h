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
	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BuffName;

	// ���� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* BuffImage;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BuffPrice;
		
	// ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PersistTime;

	// ������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESupplyItemType ItemType;

	// ������ ȿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemEffect;

public:
	FSupplyItemData();
	

};
