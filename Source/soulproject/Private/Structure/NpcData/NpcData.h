// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "NpcData.generated.h"

USTRUCT()
struct FNpcData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// NPC 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	// 대화에 사용될 위젯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> DialogWidetClass;

	// 기본으로 출력시킬 대화
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DialogText;

public:
	FNpcData();

};
