// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemyController/Golem/GolemController.h"

void AGolemController::OnBlackboardKeyInitialize(UBlackboardComponent* blackboardComponent, APawn* inPawn)
{
	Super::OnBlackboardKeyInitialize(blackboardComponent, inPawn);

	BlackBoardComponent = blackboardComponent;

}
