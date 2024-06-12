#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GenericTeamAgentInterface.h"
#include "Enum/CharacterTeam.h"

#include "GameCharacter.generated.h"

// 무기 태그
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

	// 무기 스태틱메시 컴포넌트
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	// 한손 무기 스켈레탈메시 컴포넌트
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh_Onehanded;

	// 창 무기 스켈레탈메시 컴포넌트
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh_Spear;

	// 버프 제어 컴포넌트
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerBuffControlComponent* BuffControlComponent;


	// 추후에 삭제해야함
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

	// 게임 시작 시 플레이어의 위치를 나타냅니다.
	UPROPERTY()
	FVector StartLocation;

	// 플레이어 죽은 시간
	UPROPERTY()
	float PlayerDeadTime;

	float CurrentHp;

	// 카메라 시작 위치
	UPROPERTY()
	FVector CameraStartLocation;

	// 카메라 시작 회전
	UPROPERTY()
	FRotator CameraStartRotation;

	
	// 공격 애니메이션 재생용 현재 무기 코드입니다.
	FName CurrentWeaponCode;

public:
	// 장착된 무기 코드
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

	void Knockback(FVector direction, float power);
	void DeadBounce();


	// 플레이어 리스폰 시 호출됩니다.
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

	// 모든 무기를 숨깁니다.
	void HideAllWeaponMesh();

	// 지정한 무기메시를 보이도록 설정합니다.
	void ShowWeaponMesh(int32 weaponNumber);


	// 스태틱 메시(메인 무기) 무기 숨김
	void HideStaticMeshWeapon();

	// 스켈레탈 메시 무기 숨김
	void HideSkeletalMeshWeapon();

	void SetLevelTransition(ULevelTransitionGameInstance* levelTransition);

	void SetGameInstance();
	void UpdateGameInstance();

};
