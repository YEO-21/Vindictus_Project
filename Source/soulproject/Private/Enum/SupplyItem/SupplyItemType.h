// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *  지원 아이템 타입을 위한 열거 형식입니다.
 */
UENUM(BlueprintType)
enum class ESupplyItemType : uint8
{
	AtkBase,
	DefBase,
	HpBase,
	CriticalBase

};
