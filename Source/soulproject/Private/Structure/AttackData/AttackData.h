#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AttackData.generated.h"


// ���� ������ ��Ÿ���� ����ü�Դϴ�.
USTRUCT()
struct FAttackData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ���� �̸��� ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere)
	FName AttackName;


	// ���� ������ �����ų ��� ���� �̸��� �޺����� �����մϴ�.
	UPROPERTY(EditAnywhere)
	TArray<FName> LinkableAttackSectionNames;

	// �����ų �ִ� ��Ÿ�� ������ ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere)
	class UAnimMontage* UseAnimMontage;

	// ���� �����
	UPROPERTY(EditAnywhere)
	float AttackDamage;

	// �� ������ ����� �� ī�޶� �� ������ �ٶ󺸵��� �� ������
	UPROPERTY(EditAnywhere)
	bool LookForward;


	int32 GetMaxComboCount() const
	{
		return LinkableAttackSectionNames.Num();
	}
};
