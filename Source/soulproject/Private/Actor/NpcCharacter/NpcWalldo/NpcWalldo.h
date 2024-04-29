#pragma once

#include "CoreMinimal.h"
#include "Actor/NpcCharacter/NpcCharacter.h"
#include "NpcWalldo.generated.h"

UCLASS()
class ANpcWalldo : public ANpcCharacter
{
	GENERATED_BODY()

private:
	TSubclassOf<class UWeaponStoreWidget> BP_WeaponStoreWidgetClass;


public :
	ANpcWalldo();

	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished) override;
	
	virtual class UInteractionParamBase* GetInteractionParam() override;

};
