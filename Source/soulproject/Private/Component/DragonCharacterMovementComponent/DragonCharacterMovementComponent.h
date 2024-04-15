// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragonCharacterMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDragonCharacterMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class ADragonCharacter * DragonCharacter;

	UPROPERTY()
	bool IsDash;

	UPROPERTY()
	bool IsFly;

	UPROPERTY()
	bool IsFalling;

	UPROPERTY()
	float FlyTargetHeight;

	UPROPERTY()
	FVector BodyMeshLocation;

	


	UPROPERTY()
	bool IsYawTurning;

	// ��ǥ Yaw ȸ����
	UPROPERTY()
	float TargetYawAngle;


public:	
	UDragonCharacterMovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	void TurningSmooth(float dt);


	// ��� ���� ����մϴ�.
	void CheckDashFinish();

	void FlyMovement(float dt);


public:
	// ��ǥ Yaw ȸ������ �����մϴ�.
	void SetTargetYawAngle(float targetYawAngle);

	// ������ ��ǥ Yaw �� ȸ����ŵ�ϴ�.
	void StartTurn();

	// ������ ���̷� ���ƿ����ϴ�.
	void StartFlyUp(float targetHeight);

	// �������� �����մϴ�.
	void StartFalling();

	void FinishFlying();

	void StartDash(FVector direction, float power);

	bool IsYawTernFinished();

	FORCEINLINE bool GetDashState() const 
	{
		return IsDash;
	}

	FORCEINLINE bool GetYawTurningState() const
	{
		return IsYawTurning;
	}
		
	FORCEINLINE bool GetFlyState() const
	{
		return IsFly;
	}

};
