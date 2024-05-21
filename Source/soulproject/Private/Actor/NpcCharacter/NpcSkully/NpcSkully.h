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
	TSubclassOf<class UUserWidget> BP_SkullyItemWidget;

public:
	ANpcSkully();
	
	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished) override;

	virtual class UInteractionParamBase* GetInteractionParam() override;

};
