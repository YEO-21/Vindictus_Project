// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WolfAttack.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_WolfAttack : public UBTTaskNode
{
	GENERATED_BODY()

public :
	// 공격 요청되었음 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackRequestedKey;

	// 공격중임을 나타내는 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackingKey;


public :
	UBTTask_WolfAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
