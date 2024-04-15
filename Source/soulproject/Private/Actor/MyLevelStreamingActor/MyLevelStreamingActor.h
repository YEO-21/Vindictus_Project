// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyLevelStreamingActor.generated.h"

UCLASS()
class AMyLevelStreamingActor : public AActor
{
	GENERATED_BODY()




protected:
	// 로드시킬 레벨 이름을 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LoadLevelName;


	// 레벨 스트리밍을 위하여 트리거 역할을 하는 컴포넌트입니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* Bounds;
	
public:	
	// Sets default values for this actor's properties
	AMyLevelStreamingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);




};
