// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZoomableSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class UZoomableSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

private :
	// ī�޶� �ܿ� ������ �¼��Դϴ�.
	float ZoomMultiplier;

	// ī�޶� �� �����Դϴ�.
	float ZoomLengthMin;
	float ZoomLengthMax;

public :
	UZoomableSpringArmComponent();



public :
	void ZoomCamera(float axis);
	
};
