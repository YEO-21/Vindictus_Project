// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableAreaComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnInteractionFinishEventSignature)

/**
 * 
 */
UCLASS()
class UInteractableAreaComponent : public USphereComponent
{
	GENERATED_BODY()
	
public :
	UInteractableAreaComponent();

	//  ��ȣ�ۿ��� �����մϴ�.
	bool StartInteraction(FOnInteractionFinishEventSignature onInteractionFinished);

	void SetIsFullFill();

private :
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);



};
