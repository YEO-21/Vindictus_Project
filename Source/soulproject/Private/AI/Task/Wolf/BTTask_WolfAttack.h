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
	// ���� ��û�Ǿ��� Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackRequestedKey;

	// ���������� ��Ÿ���� Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackingKey;


public :
	UBTTask_WolfAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
