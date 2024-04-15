// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateDistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_UpdateDistanceToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector PlayerCharacterActorKey;
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector DistanceToPlayerKey;

public :
	UBTTask_UpdateDistanceToPlayer();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;
	
};
