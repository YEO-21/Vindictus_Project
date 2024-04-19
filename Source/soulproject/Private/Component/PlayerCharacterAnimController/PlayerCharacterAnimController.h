// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterAnimController.generated.h"

// 다음 공격 입력 확인을 위한 대리자 형식
DECLARE_DELEGATE(FCheckNextInputEventSignature);

// 공격 영역 활성화/비활성화를 위한 대리자 형식
DECLARE_DELEGATE(FAttackAreaEnableEventSignature);

// 이동 입력 컨트롤을 위한 대리자 형식
DECLARE_DELEGATE_OneParam(FMovementInputControlEventSignature, bool /** allowMovement */);

// 구르기 이동 애님 끝 대리자 형식
DECLARE_DELEGATE(FRollAnimFinishedEventSignature);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterAnimController : public UActorComponent
{
	GENERATED_BODY()

private :

	// 이 컴포넌트가 제어할 애님 인스턴스입니다.
	UPROPERTY()
	class UPlayerCharacterAnimInstance* ControlledAnimInstance;

	UPROPERTY()
	class AGameCharacter* OwnerCharacter;

public :
	// 다음 공격 입력 확인 시작 시 발생하는 이벤트
	FCheckNextInputEventSignature onNextAttackInputCheckStarted;

	// 다음 공격 입력 확인이 끝나는 경우 발생하는 이벤트
	FCheckNextInputEventSignature onNextAttackInputCheckFinished;

	// 공격 영역 활성화 시점에서 발생하는 이벤트
	FAttackAreaEnableEventSignature onAttackAreaEnabled;

	// 공격 영역 비활성화 시점에서 발생하는 이벤트
	FAttackAreaEnableEventSignature onAttackAreaDisabled;

	// 이동 입력이 제어될 때 발생하는 이벤트
	FMovementInputControlEventSignature onAllowMovementInput;

	// 구르기 입력이 끝났을 때 발생하는 이벤트
	FRollAnimFinishedEventSignature onRollAnimFinished;

	


public:	
	UPlayerCharacterAnimController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 제어할 AnimInstance 객체를 설정합니다.
	// controlledAnimInstance : 제어시킬 AnimInstance 객체를 전달합니다.
	void SetAnimInstance(class UPlayerCharacterAnimInstance* controlledAnimInstance);

	// 공격이 끝났을 경우 호출됩니다.
	void OnAttackEnded();

	// 다음 공격 입력 확인이 시작되었을 때 호출됩니다.
	void OnNextAttackCheckStarted();

	// 다음 공격 입력 확인이 끝났을 때 호출됩니다.
	void OnNextAttackCheckFinished();

	void EnableAttackArea();

	void DisableAttackArea();

	void AllowMovementInput(bool allowMovementInput);

	void OnHitFinished();

	// 구르기 애니메이션이 끝났을 경우 호출됩니다.
	void OnRollFinished();

	// 구르기 애니메이션 시작
	void OnRollStart();


};
