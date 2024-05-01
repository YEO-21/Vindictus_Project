// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private :
	// �ִϸ��̼��� ��Ʈ���ϴ� ��ü�Դϴ�.
	class UPlayerCharacterAnimController* AnimController;

protected :
	// ĳ���Ϳ� ����� ���� �ӷ��� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentSpeed;

	// ĳ���Ͱ� ���� ��������� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGrounded;

	// ĳ���Ͱ� ��������� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsBlock;

	// �÷��̾ ��������� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPlayerDead;
	
	// �÷��̾��� ���� ���Ⱑ �Ѽ� ���������� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOneHandedWeapon;

	// �÷��̾��� ���� ���Ⱑ â ������ ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsSpear;


public :
	// �ִ� ��Ʈ�ѷ��� �����մϴ�.
	void SetAnimController(class UPlayerCharacterAnimController* animController);

	FORCEINLINE UPlayerCharacterAnimController* GetAnimController() const
	{
		return AnimController;
	}

	void SetCurrentSpeed(float currentSpeed);
	void SetGroundedState(bool isGrounded);
	void SetBlockState(bool isBlocking);
	void SetPlayerDeadState(bool isdead);
	void SetOneHandedWeapon(bool onehand);
	void SetSpear(bool spear);


private:
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_StartNextAttackCheck();

	UFUNCTION()
	void AnimNotify_FinishNextAttackCheck();

	UFUNCTION()
	void AnimNotify_EnableAttackArea();

	UFUNCTION()
	void AnimNotify_DisableAttackArea();


	UFUNCTION()
	void AnimNotify_BlockMovementInput();

	UFUNCTION()
	void AnimNotify_AllowMovementInput();

	UFUNCTION()
	void AnimNotify_HitFinished();

	UFUNCTION()
	void AnimNotify_RollFinished();

	UFUNCTION()
	void AnimNotify_RollStart();



};
