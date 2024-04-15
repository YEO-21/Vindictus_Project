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
	// 공격적 상태를 나타내는 블랙보드 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAggressiveStateKey;

	// 마지막으로 피해를 입은 시간이 기록된 블랙보트 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector LastDamagedTimeKey;

	// 공격적 상태가 끝나기까지 걸리는 시간을 나타내는 블랙보드 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TimeToCalmDownKey;

public :
	UBTService_UpdateAggressiveState();

protected :
	virtual void TickNode(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory, float deltaSeconds) override;

};
