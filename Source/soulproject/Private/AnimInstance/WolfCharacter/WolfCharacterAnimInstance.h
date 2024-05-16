// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WolfCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UWolfCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float WolfStateNumber;

public:
	void SetCurrentSpeed(float newSpeed);

	void SetWolfStateNumber(float newNumber);

private :
	UFUNCTION()
	void AnimNotify_OnAttackFinished();

	
};
