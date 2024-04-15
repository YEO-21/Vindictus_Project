// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerCharacterData.generated.h"

/**
 * �÷��̾� ĳ������ �⺻ ������ ��Ÿ���� ���� ����ü
 */
USTRUCT()
struct FPlayerCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHp;

	// �ִ� ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxStamina;

	// ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Atk;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Def;
};
