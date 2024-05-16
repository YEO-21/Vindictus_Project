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
	// �� ���� ������ ���̺� ����
	class UDataTable* EnemyDataTable;

protected :
	// �� ������
	struct FEnemyData* EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyCharacter> BP_EnemyCharacter;

	// ���� ü��
	UPROPERTY()
	float CurrentHp;

	// ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;

	// �� �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EnemyCode;

	// ���������� ���ݹ��� �ð��� ��Ÿ���ϴ�.
	UPROPERTY()
	float LastDamagedTime;

	// ��� �� ���� ���͸���
	UPROPERTY()
	class UMaterialInstanceDynamic* MaterialInstanceOnDead;

	// �� ĳ���� ��� ��ġ
	UPROPERTY()
	FTransform DeadLocation;

	FTimerHandle HUDShowTimerHandle;
	FTimerHandle RespawnTimerHandle;


public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	// ��Ʈ�ѷ��� ĳ���Ϳ� ���ǵǾ��� �� ȣ��˴ϴ�.
	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LaunchCharacter(FVector direction, float power);

	void PlayerDead();
	void PlayerRespawn();

private :
	// �� ������ �ʱ�ȭ�մϴ�.
	void InitializeEnemyData();

	UFUNCTION()
	void OnDamaged(
		// ������� ���� ����
		AActor* DamagedActor, 
		// ���ط�
		float Damage, 
		// ����� ����
		const class UDamageType* DamageType, 
		// ���ظ� ���� ���� ��Ʈ�ѷ�
		class AController* InstigatedBy, 
		// ���� ����
		AActor* DamageCauser);

	// ��� ���͸���� �����մϴ�.
	void ChangeMaterialToDeadState();

	// ������ �մϴ�.
	void PlayRagdoll();



protected :
	// �� ��Ʈ�ѷ��� �����մϴ�.
	virtual void SetEnemyController(TSubclassOf<class AEnemyController> controllerClass, 
		EAutoPossessAI possessType = EAutoPossessAI::PlacedInWorldOrSpawned);

	// ������� ���� ��� ȣ��˴ϴ�.
	// gameCharacter : GameCharacter ��ü�� ���޵˴ϴ�.
	// damage : ������ ����� ��ġ�� ���޵˴ϴ�.
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage);

	// ���� ����� ��� ȣ��Ǵ� �޼����Դϴ�.
	virtual void OnDead();

	// ���� ���ŵ� �� ȣ��˴ϴ�.
	virtual void OnEnemyDestroy();

	// ������� ����մϴ�.
	// damage : ���� ���ط��� ���޵˴ϴ�.
	// return : ������ ����� ��ġ�� ��ȯ�մϴ�.
	virtual float CalculateDamage(float damage);

	// �������� �մϴ�.
	virtual void EnemyRespawn();

	virtual void SetEnemyClass();

public :

	// �� �����͸� ��ȯ�մϴ�.
	FORCEINLINE const struct FEnemyData* GetEnemyData() const
	{
		return EnemyData;
	}

	// ���� ü���� ��ȯ�մϴ�.
	FORCEINLINE float GetCurrentHp() const
	{
		return CurrentHp;
	}

	// ��� ���¸� ��ȯ�մϴ�.
	FORCEINLINE bool IsDeadState() const
	{
		return IsDead;
	}

};
