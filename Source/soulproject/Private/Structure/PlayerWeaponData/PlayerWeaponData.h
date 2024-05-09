#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/Weapon/WeaponType.h"
#include "PlayerWeaponData.generated.h"

/**
 * 플레이어 무기에 대한 정보를 나타내는 구조체입니다.
 */
USTRUCT()
struct FPlayerWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// 무기 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	// 무게
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Atk;

	// 애님 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AnimMontage;

	// 무기 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* WeaponStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMesh* WeaponSkeletalMesh;

	// 무기 가격
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Price;

	// UI용 무기 이미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTexture2D* WeaponImage;

	// 무기 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* AttackEffect;

	// 무기 피격 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* AttackHitEffect;


	// 특수 능력
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)



};
