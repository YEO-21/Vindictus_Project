#pragma once

#include "CoreMinimal.h"

/// <summary>
/// 월드 무기 타입을 나타내기 위한 열거 형식입니다.
/// </summary>
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	RANGE_WEAPON_START = 0,
	SHARPNER = 1				UMETA(DisplayName = "Sharpner"),
	STORM_BREAKER = 2			UMETA(DisplayName = "Storm Breaker"),
	TWIN_DRAGON_SWORD = 3		UMETA(DisplayName = "Twin Dragon Sword"),
	WALLDO = 4					UMETA(DisplayName = "Walldo"),
	NAMELESS_SPEAR = 5			UMETA(DisplayName = "Nameless Spear"),
	RANGE_WEAPON_END = 6

};
