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
	// �ε��ų ���� �̸��� ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LoadLevelName;


	// ���� ��Ʈ������ ���Ͽ� Ʈ���� ������ �ϴ� ������Ʈ�Դϴ�.
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
