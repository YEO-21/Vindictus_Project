#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/Weapon/WeaponType.h"
#include "PlayerWeaponData.generated.h"

/**
 * �÷��̾� ���⿡ ���� ������ ��Ÿ���� ����ü�Դϴ�.
 */
USTRUCT()
struct FPlayerWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	// ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Atk;

	// �ִ� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AnimMontage;

	// ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* WeaponStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMesh* WeaponSkeletalMesh;

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Price;

	// UI�� ���� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTexture2D* WeaponImage;

	// ���� ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* AttackEffect;

	// ���� �ǰ� ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* AttackHitEffect;


	// Ư�� �ɷ�
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)



};
