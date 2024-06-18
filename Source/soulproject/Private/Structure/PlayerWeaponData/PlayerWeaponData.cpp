#include "PlayerWeaponData.h"

FPlayerWeaponData::FPlayerWeaponData()
{
	Name = TEXT("");
	Weight = Atk = 0.0f;
	AnimMontage = nullptr;
	WeaponType = EWeaponType::RANGE_WEAPON_START;
	WeaponStaticMesh = nullptr;
	WeaponSkeletalMesh = nullptr;
	Price = 0.0f;
	StoreWeaponImage = nullptr;
	AttackEffect = nullptr;
	AttackHitEffect = nullptr;
}
