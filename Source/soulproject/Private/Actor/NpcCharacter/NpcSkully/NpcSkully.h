#pragma once

#include "CoreMinimal.h"
#include "Actor/NpcCharacter/NpcCharacter.h"
#include "NpcSkully.generated.h"

/**
 * 
 */
UCLASS()
class ANpcSkully : public ANpcCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TSubclassOf<class USupplyStoreWidget> BP_SupplyItemStoreWidgetClass;


public:
	ANpcSkully();
	
	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished) override;

	virtual class UInteractionParamBase* GetInteractionParam() override;

};
