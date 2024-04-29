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

public:
	ANpcSkully();
	
	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished,
		class UInteractionParamBase* interactionParam) override;

};
