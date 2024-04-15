// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAt.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_LookAt : public UBTTaskNode
{
	GENERATED_BODY()
	
public :
	// �̵� �½�ũ ������ Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsMoveTaskRunningKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetActorKey;

private :
	UPROPERTY()
	bool YawTerningStarted;

	// ��ǥ ȸ������ ��Ÿ���ϴ�.
	UPROPERTY()
	FRotator TargetRotation;

public :
	UBTTask_LookAt();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public :
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;

};
