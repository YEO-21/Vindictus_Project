// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KnightCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UKnightCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentSpeed;

public :
	void SetCurrentSpeed(float newSpeed);

private :
	UFUNCTION()
	void AnimNotify_OnAttackFinished();

	UFUNCTION()
	void AnimNotify_EnableAttackArea();

	UFUNCTION()
	void AnimNotify_DisableAttackArea();

	UFUNCTION()
	void AnimNotify_ParriedMotionFinished();

	UFUNCTION()
	void AnimNotify_HitMotionFinished();

	
};
