#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_GetPlayerLocation : public UBTService
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseMaxTrackingDistance;



public :
	UBTService_GetPlayerLocation();

	virtual void TickNode(
		UBehaviorTreeComponent& ownerComponent,
		uint8* nodeMemory,
		float dt) override;
};
