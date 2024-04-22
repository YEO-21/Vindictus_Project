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

	// ���ظ� �Ծ��� ��� �����ų �ִ� ��Ÿ��
	UPROPERTY()
	class UAnimMontage* HitAnimMontage;

	// �׾��� �� ����� �ִϸ��̼�
	UPROPERTY()
	class UAnimMontage* DeadAnimMontage;

	// ���� ���ظ� �Դ������� ��Ÿ���ϴ�.
	UPROPERTY()
	bool IsHit;

	// ���� ��ü Ȯ���� ���� �����Դϴ�.
	UPROPERTY()
	int32 WeaponCount;

	// ���� �׾����� ���¸� ��Ÿ���ϴ�.
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

	// ĳ���� �����Ͱ� ���ŵ� �� ȣ��˴ϴ�.
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
