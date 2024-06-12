#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GenericTeamAgentInterface.h"
#include "Enum/CharacterTeam.h"

#include "GameCharacter.generated.h"

// ���� �±�
#define WEAPON_SHARPNER			TEXT("DefaultAttack")
#define WEAPON_STORMBREAKER		TEXT("AxeAttack")
#define WEAPON_SPEAR			TEXT("SpearAttack")


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
	class UPlayerEquipWeaponComponent* EquipWeaponComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBossCriticalAttackComponent* BossCriticalAttackComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAttackNiagaraSystem* AttackNiagaraSystem;

	// ���� ����ƽ�޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	// �Ѽ� ���� ���̷�Ż�޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh_Onehanded;

	// â ���� ���̷�Ż�޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh_Spear;

	// ���� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerBuffControlComponent* BuffControlComponent;


	// ���Ŀ� �����ؾ���
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

	// ���� ���� �� �÷��̾��� ��ġ�� ��Ÿ���ϴ�.
	UPROPERTY()
	FVector StartLocation;

	// �÷��̾� ���� �ð�
	UPROPERTY()
	float PlayerDeadTime;

	float CurrentHp;

	// ī�޶� ���� ��ġ
	UPROPERTY()
	FVector CameraStartLocation;

	// ī�޶� ���� ȸ��
	UPROPERTY()
	FRotator CameraStartRotation;

	
	// ���� �ִϸ��̼� ����� ���� ���� �ڵ��Դϴ�.
	FName CurrentWeaponCode;

public:
	// ������ ���� �ڵ�
	UPROPERTY()
	FName EquippedWeaponCode;

	UPROPERTY()
	class ULevelTransitionGameInstance* LevelTransitionGameInstance;



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

	void SetPlayerRespawn();

	void UpdateWeaponSocket();
	

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

	void Knockback(FVector direction, float power);
	void DeadBounce();


	// �÷��̾� ������ �� ȣ��˴ϴ�.
	void Respawn(FVector respawnlocation, float respawntime);




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

	FORCEINLINE class UPlayerEquipWeaponComponent* GetEquipWeaponComponent() const
	{
		return EquipWeaponComponent;
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

	FORCEINLINE float GetCurrentHp()
	{
		return CurrentHp;
	}

	FORCEINLINE FVector GetStartLocation()
	{
		return StartLocation;
	}

	FORCEINLINE FName GetCurrentWeaponCode()
	{
		return CurrentWeaponCode;
	}

	FORCEINLINE UStaticMeshComponent* GetWeaponMesh()
	{
		return	WeaponMesh;
	}

	FORCEINLINE USkeletalMeshComponent* GetSubWeaponMesh()
	{
		return	SubWeaponMesh;
	}

	FORCEINLINE USkeletalMeshComponent* GetWeaponMeshOneHanded()
	{
		return	WeaponMesh_Onehanded;
	}

	FORCEINLINE USkeletalMeshComponent* GetWeaponMeshSpear()
	{
		return	WeaponMesh_Spear;
	}

	FORCEINLINE UAttackNiagaraSystem* GetAttackNiagaraSystem()
	{
		return AttackNiagaraSystem;
	}

	FORCEINLINE UBossCriticalAttackComponent* GetUBossCriticalAttackComponent()
	{
		return BossCriticalAttackComponent;
	}

	FORCEINLINE class UPlayerBuffControlComponent* GetBuffControlComponent()
	{
		return BuffControlComponent;
	}
	
	void SetPlayerDeadTime(float time);
	void SetCurrentHp(float currenthp);
	void SetCameraDeadView();
	void SetCurrentWeaponCode(FName weaponCode);
	void RespawnCameraView();

	// ��� ���⸦ ����ϴ�.
	void HideAllWeaponMesh();

	// ������ ����޽ø� ���̵��� �����մϴ�.
	void ShowWeaponMesh(int32 weaponNumber);


	// ����ƽ �޽�(���� ����) ���� ����
	void HideStaticMeshWeapon();

	// ���̷�Ż �޽� ���� ����
	void HideSkeletalMeshWeapon();

	void SetLevelTransition(ULevelTransitionGameInstance* levelTransition);

	void SetGameInstance();
	void UpdateGameInstance();

};
