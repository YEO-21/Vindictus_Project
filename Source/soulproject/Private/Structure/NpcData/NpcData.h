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
	// NPC �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	// ��ȭ�� ���� ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> DialogWidetClass;

	// �⺻���� ��½�ų ��ȭ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DialogText;

public:
	FNpcData();

};
