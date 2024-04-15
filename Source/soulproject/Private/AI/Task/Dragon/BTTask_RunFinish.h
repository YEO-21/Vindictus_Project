// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RunFinish.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_RunFinish : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector DistanceToPlayerKey;


private:
	UPROPERTY()
	bool bRushAttackAnimationStarted;
	




public:
	UBTTask_RunFinish();

protected:
	virtual void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMem, float dt) override;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMem) override;

	
};
