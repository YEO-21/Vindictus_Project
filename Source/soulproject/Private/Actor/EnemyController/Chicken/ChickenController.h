// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyController/EnemyController.h"
#include "ChickenController.generated.h"


/**
 * 
 */
UCLASS()
class AChickenController : public AEnemyController
{
	GENERATED_BODY()


protected :
	virtual void OnBlackboardKeyInitialize(class UBlackboardComponent* blackboardComponent, class APawn* inPawn) override;
	
};
