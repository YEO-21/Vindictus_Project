// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DragonCharacterAttackComponent/DragonCharacterAttackComponent.h"

// Sets default values for this component's properties
UDragonCharacterAttackComponent::UDragonCharacterAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDragonCharacterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDragonCharacterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 드래곤의 공격을 감지합니다.
	if (bIsAttackCheckEnabled) CheckAttackArea();

	// ...
}

void UDragonCharacterAttackComponent::StartBreathFire()
{
	IsBreathFire = true;
}

void UDragonCharacterAttackComponent::OnBreathFireFinished()
{
	IsBreathFire = false;
}

void UDragonCharacterAttackComponent::StartClawAttack()
{
	IsClawAttack = true;
}

void UDragonCharacterAttackComponent::FinishClawAttack()
{
	IsClawAttack = false;
}

void UDragonCharacterAttackComponent::StartRushAttack()
{
	IsRushAttack = true;
}

void UDragonCharacterAttackComponent::FinishRushAttack()
{
	IsRushAttack = false;
}

void UDragonCharacterAttackComponent::CheckAttackArea()
{
}

