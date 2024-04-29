#pragma once

#include "CoreMinimal.h"
#include "Object/InteractionParam/InteractionParamBase.h"
#include "WeaponNpcInteractParam.generated.h"

UCLASS()
class UWeaponNpcInteractParam : public UInteractionParamBase
{
	GENERATED_BODY()

protected:
	virtual void InteractNpcParam(ENpcType npcType) override;
	
};
