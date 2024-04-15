// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NpcAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNpcAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsTalking;

public :
	void SetTalkState(bool isTalking);
	
};
