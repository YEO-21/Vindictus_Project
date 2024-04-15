// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateAggressiveState.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_UpdateAggressiveState : public UBTService
{
	GENERATED_BODY()
	
protected :
	// ������ ���¸� ��Ÿ���� ������ Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAggressiveStateKey;

	// ���������� ���ظ� ���� �ð��� ��ϵ� ����Ʈ Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector LastDamagedTimeKey;

	// ������ ���°� ��������� �ɸ��� �ð��� ��Ÿ���� ������ Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TimeToCalmDownKey;

public :
	UBTService_UpdateAggressiveState();

protected :
	virtual void TickNode(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory, float deltaSeconds) override;

};
