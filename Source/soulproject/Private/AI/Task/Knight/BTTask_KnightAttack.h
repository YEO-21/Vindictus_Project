// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_KnightAttack.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_KnightAttack : public UBTTaskNode
{
	GENERATED_BODY()

public :
	// ���� ��û�� Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackRequestedKey;

	// ������ Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackingKey;

public :
	UBTTask_KnightAttack();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;
	
};
