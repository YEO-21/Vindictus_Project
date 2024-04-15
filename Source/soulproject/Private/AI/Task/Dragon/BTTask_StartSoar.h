#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StartSoar.generated.h"

UCLASS()
class UBTTask_StartSoar : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool FlyStarted;


public:
	UBTTask_StartSoar();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComp, uint8* newMem) override;
	
};
