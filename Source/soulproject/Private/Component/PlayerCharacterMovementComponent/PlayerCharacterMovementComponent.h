// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterMovementComponent : public UActorComponent
{
	GENERATED_BODY()
private :

	UPROPERTY()
	class AGameCharacter* GameCharacter;

	UPROPERTY()
	class UAnimMontage* RollAnimMontage;

	// 이동 입력 허용 상태를 나타냅니다.
	bool AllowMovementInput;

	// 이전에 입력된 구르기 방향
	FIntVector2 PrevRollInputDirection;

	// 구르기 입력 시간
	float RollInputTime;

	// 현재 구르기중임을 나타냅니다.
	UPROPERTY()
	bool IsRollingMovement;

	// 달리기 상태임을 나타냅니다.
	UPROPERTY()
	bool IsRun;

	

public:	
	UPlayerCharacterMovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HorizontalMove(float axis);
	void VerticalMove(float axis);
	void OnJump();
	void OnHit();
	void OnRollInput(FIntVector2 inputDirection);
	void OnRollFinished();
	void OnRunStarted();
	void OnRunFinished();

	// 이동 입력 허용 상태를 설정합니다.
	// allowMovementInput : 허용하는 경우 True 를 전달합니다.
	void SetAllowMovementInput(bool allowMovementInput);

	// 충격을 가합니다.
	void AddImpulse(FVector direction, float power);

	void StartRollingMovmement();


private :
	// 구르기 이동을 실행합니다.
	void RollingMovement(FVector rollDirection, FIntVector2 inputDirection);


public :
	FORCEINLINE bool GetRollingState() const
	{
		return IsRollingMovement;
	}

	FORCEINLINE bool GetRunState() const
	{
		return IsRun;
	}





		
};
