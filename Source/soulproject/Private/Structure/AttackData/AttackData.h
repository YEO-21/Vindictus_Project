#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AttackData.generated.h"


// 공격 정보를 나타내는 구조체입니다.
USTRUCT()
struct FAttackData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 공격 이름을 나타냅니다.
	UPROPERTY(EditAnywhere)
	FName AttackName;


	// 같은 공격을 연계시킬 경우 섹션 이름을 콤보별로 정리합니다.
	UPROPERTY(EditAnywhere)
	TArray<FName> LinkableAttackSectionNames;

	// 재생시킬 애님 몽타주 에셋을 나타냅니다.
	UPROPERTY(EditAnywhere)
	class UAnimMontage* UseAnimMontage;

	// 공격 대미지
	UPROPERTY(EditAnywhere)
	float AttackDamage;

	// 이 공격이 실행될 때 카메라 앞 방향을 바라보도록 할 것인지
	UPROPERTY(EditAnywhere)
	bool LookForward;


	int32 GetMaxComboCount() const
	{
		return LinkableAttackSectionNames.Num();
	}
};
