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

	// 판매 아이템 목록
	//UDataTable*;
	//TArray<FString/*itemCode*/>;


};



// UNpcDialogWidget 클래스를 상속받는 클래스
// - 상점 창 띄우기 메서드()