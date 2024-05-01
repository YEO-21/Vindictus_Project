#pragma once

#include "CoreMinimal.h"
#include "Object/InteractionParam/InteractionParamBase.h"
#include "WeaponNpcInteractParam.generated.h"

UCLASS()
class UWeaponNpcInteractParam : public UInteractionParamBase
{
	GENERATED_BODY()

public :
	// 판매 아이템 목록
	TArray<FName> SaleItemCodes;
	TSubclassOf<class UWeaponStoreWidget> BP_WeaponStoreWidgetClass;

};
