// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DashBackward.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_DashBackward : public UBTTaskNode
{
	GENERATED_BODY()

public :
	// 이동 태스크 실행중 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsMoveTaskRunningKey;

public :
	UBTTask_DashBackward();

protected :
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


public :
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;

};
