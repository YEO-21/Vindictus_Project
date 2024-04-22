#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GenericTeamAgentInterface.h"
#include "Enum/CharacterTeam.h"

#include "GameCharacter.generated.h"

UCLASS()
class AGameCharacter : public ACharacter, 
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerCharacterMovementComponent* PlayerCharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerCharacterAnimController* PlayerCharacterAnimController;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerCharacterAttackComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerCharacterInteractComponent* InteractComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SubWeaponMesh;

	FGenericTeamId Team;

	// 피해를 입었을 경우 재생시킬 애님 몽타주
	UPROPERTY()
	class UAnimMontage* HitAnimMontage;

	// 죽었을 때 재생할 애니메이션
	UPROPERTY()
	class UAnimMontage* DeadAnimMontage;

	// 현재 피해를 입는중임을 나타냅니다.
	UPROPERTY()
	bool IsHit;

	// 무기 교체 확인을 위한 변수입니다.
	UPROPERTY()
	int32 WeaponCount;

	// 현재 죽었는지 상태를 나타냅니다.
	UPROPERTY()
	bool IsDead;



public:
	AGameCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private :
	UFUNCTION()
	void OnDamaged(
		AActor* damagedActor,
		float damage,
		const class UDamageType* damageType,
		class AController* instigatedBy,
		AActor* damageCauser);

public:	
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;

	// 캐릭터 데이터가 갱신될 때 호출됩니다.
	void OnPlayerCharacterDataUpdated(const struct FPlayerCharacterData* const playerCharacterData);

	void OnHorizontalInput(float axis);
	void OnVerticalInput(float axis);
	void OnZoomInput(float axis);
	void OnJumpInput();
	void OnAttackInput();
	void OnInteractInput();

	void OnRollForward();
	void OnRollBackward();
	void OnRollRight();
	void OnRollLeft();

	void OnBlockStarted();
	void OnBlockFinished();

	void OnRunStarted();
	void OnRunFinished();
	void OnStaminaEmpty();

	void OnHitFinished();

	void OnWeaponChanged();

	void PlayAttackBlockAnim();

	void PlayDeadAnim();
	void DeadBounce();


	FORCEINLINE class UPlayerCharacterMovementComponent* GetPlayerCharacterMovementComponent() const
	{
		return PlayerCharacterMovementComponent;
	}

	FORCEINLINE class UPlayerCharacterAttackComponent* GetAttackComponent() const
	{ 
		return AttackComponent;
	}

	FORCEINLINE class UPlayerCharacterInteractComponent* GetInteractComponent() const
	{
		return InteractComponent;
	}

	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{
		Team = TeamID;
	}

	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override 
	{ 
		return Team;
	}

	FORCEINLINE bool GetHitState() const
	{
		return IsHit;
	}

	FORCEINLINE void SetDeadState(bool isdead)
	{
		IsDead = isdead;
	}

	FORCEINLINE bool GetDeadState()
	{
		return IsDead;
	}

};
