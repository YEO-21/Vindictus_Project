#pragma once

#include "CoreMinimal.h"

/// <summary>
/// ���� ���� Ÿ���� ��Ÿ���� ���� ���� �����Դϴ�.
/// </summary>
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	RANGE_WEAPON_START = 0,
	SHARPNER = 1				UMETA(DisplayName = "Sharpner"),
	STORM_BREAKER = 2			UMETA(DisplayName = "Storm Breaker"),
	TWIN_DRAGON_SWORD = 3		UMETA(DisplayName = "Twin Dragon Sword"),
	RANGE_WEAPON_END = 4

};
