// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"




UCLASS()
class AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComponent;

public :
	// 적 정보 데이터 테이블 에셋
	class UDataTable* EnemyDataTable;

protected :
	// 적 데이터
	struct FEnemyData* EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyCharacter> BP_EnemyCharacter;

	// 현재 체력
	UPROPERTY()
	float CurrentHp;

	// 사망 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;

	// 적 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EnemyCode;

	// 마지막으로 공격받은 시간을 나타냅니다.
	UPROPERTY()
	float LastDamagedTime;

	// 사망 시 사용될 메터리얼
	UPROPERTY()
	class UMaterialInstanceDynamic* MaterialInstanceOnDead;

	// 적 캐릭터 사망 위치
	UPROPERTY()
	FTransform DeadLocation;

	FTimerHandle HUDShowTimerHandle;
	FTimerHandle RespawnTimerHandle;


public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	// 컨트롤러가 캐릭터에 빙의되었을 때 호출됩니다.
	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LaunchCharacter(FVector direction, float power);

	void PlayerDead();
	void PlayerRespawn();

private :
	// 적 정보를 초기화합니다.
	void InitializeEnemyData();

	UFUNCTION()
	void OnDamaged(
		// 대미지를 입은 액터
		AActor* DamagedActor, 
		// 피해량
		float Damage, 
		// 대미지 종류
		const class UDamageType* DamageType, 
		// 피해를 입힌 가해 컨트롤러
		class AController* InstigatedBy, 
		// 가해 액터
		AActor* DamageCauser);

	// 사망 메터리얼로 변경합니다.
	void ChangeMaterialToDeadState();

	// 랙돌을 켭니다.
	void PlayRagdoll();



protected :
	// 적 컨트롤러를 설정합니다.
	virtual void SetEnemyController(TSubclassOf<class AEnemyController> controllerClass, 
		EAutoPossessAI possessType = EAutoPossessAI::PlacedInWorldOrSpawned);

	// 대미지를 입은 경우 호출됩니다.
	// gameCharacter : GameCharacter 객체가 전달됩니다.
	// damage : 가공된 대미지 수치가 전달됩니다.
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage);

	// 적이 사망한 경우 호출되는 메서드입니다.
	virtual void OnDead();

	// 적이 제거될 때 호출됩니다.
	virtual void OnEnemyDestroy();

	// 대미지를 계산합니다.
	// damage : 입은 피해량이 전달됩니다.
	// return : 가공된 대미지 수치를 반환합니다.
	virtual float CalculateDamage(float damage);

	// 리스폰을 합니다.
	virtual void EnemyRespawn();

	virtual void SetEnemyClass();

public :

	// 적 데이터를 반환합니다.
	FORCEINLINE const struct FEnemyData* GetEnemyData() const
	{
		return EnemyData;
	}

	// 현재 체력을 반환합니다.
	FORCEINLINE float GetCurrentHp() const
	{
		return CurrentHp;
	}

	// 사망 상태를 반환합니다.
	FORCEINLINE bool IsDeadState() const
	{
		return IsDead;
	}

};
