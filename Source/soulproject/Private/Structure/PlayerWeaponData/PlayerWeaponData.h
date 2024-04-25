#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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



	// Ư�� �ɷ�
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)



};
