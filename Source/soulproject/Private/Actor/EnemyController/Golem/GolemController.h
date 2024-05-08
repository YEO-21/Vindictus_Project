// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyController/EnemyController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GolemController.generated.h"

/**
 * 
 */


UCLASS()
class AGolemController : public AEnemyController
{
	GENERATED_BODY()

private:
	class UBlackboardComponent* BlackboardComponent;

	bool isAttackStarted;

public:
	AGolemController();

protected:
	virtual void OnBlackboardKeyInitialize(
		class UBlackboardComponent* blackboardComponent,
		class APawn* inPawn) override;


public:
	UFUNCTION(BlueprintCallable)
	void SetAggressive(bool isAggressive, AActor* actor);

	void Attack();
	void FinishAttack();
	void SetAttackState(bool attackState);

};
