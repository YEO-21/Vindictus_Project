// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enum/Npc/NpcType.h"
#include "InteractionParamBase.generated.h"

/**
 * 
 */
UCLASS()
class UInteractionParamBase : public UObject
{
	GENERATED_BODY()
public :
	ENpcType NpcType;

	// �Ǹ� ������ ���
	//UDataTable*;
	//TArray<FString/*itemCode*/>;


};



// UNpcDialogWidget Ŭ������ ��ӹ޴� Ŭ����
// - ���� â ���� �޼���()