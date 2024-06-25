// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingAccidentVolume.generated.h"

UCLASS()
class AFallingAccidentVolume : public AActor
{
	GENERATED_BODY()

private:
	// ³«»ç ¿µ¿ªÀ» ³ªÅ¸³À´Ï´Ù.
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* FallAccidentArea;

	
public:	
	AFallingAccidentVolume();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void OverlapPlayer();


};
