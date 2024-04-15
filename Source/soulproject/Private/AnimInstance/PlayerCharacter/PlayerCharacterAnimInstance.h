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
	// 애니메이션을 컨트롤하는 객체입니다.
	class UPlayerCharacterAnimController* AnimController;

protected :
	// 캐릭터에 적용된 현재 속력을 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentSpeed;

	// 캐릭터가 땅에 닿아있음을 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGrounded;

	// 캐릭터가 방어중임을 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsBlock;


public :
	// 애님 컨트롤러를 설정합니다.
	void SetAnimController(class UPlayerCharacterAnimController* animController);

	void SetCurrentSpeed(float currentSpeed);
	void SetGroundedState(bool isGrounded);
	void SetBlockState(bool isBlocking);


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
