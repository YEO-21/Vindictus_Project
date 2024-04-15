// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BreathFire.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_BreathFire : public UBTTaskNode
{
	GENERATED_BODY()

private :
	UPROPERTY()
	bool BreathFireStarted;

public :
	UBTTask_BreathFire();

protected :
	virtual void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float dt) override;

public :
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;
	
};
