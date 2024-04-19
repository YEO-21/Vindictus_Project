// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterAnimController.generated.h"

// ���� ���� �Է� Ȯ���� ���� �븮�� ����
DECLARE_DELEGATE(FCheckNextInputEventSignature);

// ���� ���� Ȱ��ȭ/��Ȱ��ȭ�� ���� �븮�� ����
DECLARE_DELEGATE(FAttackAreaEnableEventSignature);

// �̵� �Է� ��Ʈ���� ���� �븮�� ����
DECLARE_DELEGATE_OneParam(FMovementInputControlEventSignature, bool /** allowMovement */);

// ������ �̵� �ִ� �� �븮�� ����
DECLARE_DELEGATE(FRollAnimFinishedEventSignature);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterAnimController : public UActorComponent
{
	GENERATED_BODY()

private :

	// �� ������Ʈ�� ������ �ִ� �ν��Ͻ��Դϴ�.
	UPROPERTY()
	class UPlayerCharacterAnimInstance* ControlledAnimInstance;

	UPROPERTY()
	class AGameCharacter* OwnerCharacter;

public :
	// ���� ���� �Է� Ȯ�� ���� �� �߻��ϴ� �̺�Ʈ
	FCheckNextInputEventSignature onNextAttackInputCheckStarted;

	// ���� ���� �Է� Ȯ���� ������ ��� �߻��ϴ� �̺�Ʈ
	FCheckNextInputEventSignature onNextAttackInputCheckFinished;

	// ���� ���� Ȱ��ȭ �������� �߻��ϴ� �̺�Ʈ
	FAttackAreaEnableEventSignature onAttackAreaEnabled;

	// ���� ���� ��Ȱ��ȭ �������� �߻��ϴ� �̺�Ʈ
	FAttackAreaEnableEventSignature onAttackAreaDisabled;

	// �̵� �Է��� ����� �� �߻��ϴ� �̺�Ʈ
	FMovementInputControlEventSignature onAllowMovementInput;

	// ������ �Է��� ������ �� �߻��ϴ� �̺�Ʈ
	FRollAnimFinishedEventSignature onRollAnimFinished;

	


public:	
	UPlayerCharacterAnimController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ������ AnimInstance ��ü�� �����մϴ�.
	// controlledAnimInstance : �����ų AnimInstance ��ü�� �����մϴ�.
	void SetAnimInstance(class UPlayerCharacterAnimInstance* controlledAnimInstance);

	// ������ ������ ��� ȣ��˴ϴ�.
	void OnAttackEnded();

	// ���� ���� �Է� Ȯ���� ���۵Ǿ��� �� ȣ��˴ϴ�.
	void OnNextAttackCheckStarted();

	// ���� ���� �Է� Ȯ���� ������ �� ȣ��˴ϴ�.
	void OnNextAttackCheckFinished();

	void EnableAttackArea();

	void DisableAttackArea();

	void AllowMovementInput(bool allowMovementInput);

	void OnHitFinished();

	// ������ �ִϸ��̼��� ������ ��� ȣ��˴ϴ�.
	void OnRollFinished();

	// ������ �ִϸ��̼� ����
	void OnRollStart();


};
