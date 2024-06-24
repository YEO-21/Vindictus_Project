// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "DragonCharacter.generated.h"

// Move AnimMontage Section Names...
#define ANIMMONTAGE_SECTION_DASHBACKWARD		TEXT("DashBackward")
#define ANIMMONTAGE_SECTION_TURNLEFT			TEXT("TurnLeft")
#define ANIMMONTAGE_SECTION_TURNRIGHT			TEXT("TurnRight")

// Attack AnimMontage Section Names...
#define ANIMMONTAGE_SECTION_BREATHFIRE			TEXT("BreathFire")
#define ANIMMONTAGE_SECTION_CLAWATTACK			TEXT("ClawAttack")
#define ANIMMONTAGE_SECTION_RUSHATTACK			TEXT("RushAttack")

/**
 * 
 */
UCLASS()
class ADragonCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class UAnimMontage* MoveAnimMontage;

	UPROPERTY()
	class UAnimMontage* AttackAnimMontage;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* LeftForwardLeg;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* RightForwardLeg;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* LeftBackwardLeg;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* RightBackwardLeg;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UDragonCharacterMovementComponent * DragonMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UDragonCharacterAttackComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsPlayed;

public :
	ADragonCharacter();


protected :
	virtual void BeginPlay() override;

public :
	// 이동 애니메이션 몽타주를 재생합니다.
	// playSectionName : 재생시킬 섹션명을 전달합니다.
	void PlayMoveAnimMontage(FName playSectionName);

	// 공격 애니메이션 몽타주를 재생합니다.
	// playSectionName : 재생시킬 섹션명을 전달합니다.
	void PlayAttackAnimMontage(FName playSectionName);

	UFUNCTION(BlueprintCallable)
	void OnPlayerCharacterDetected(class AGameCharacter* gameCharacter);

	FORCEINLINE class UDragonCharacterMovementComponent * GetDragonMovementComponent() const
	{
		return DragonMovementComponent;
	}

	FORCEINLINE class UDragonCharacterAttackComponent* GetAttackComponent() const
	{
		return AttackComponent;
	}

protected:
	virtual void OnDead();

	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage);
	
};
