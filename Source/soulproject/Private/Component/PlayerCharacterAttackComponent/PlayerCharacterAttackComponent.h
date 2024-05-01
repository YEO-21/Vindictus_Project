// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterAttackComponent.generated.h"

// �ƹ� ���ݵ� �ϰ����� ������ ��Ÿ�� ��ũ�� ���
#define ATTACK_NONE				TEXT("NONE")

// �⺻ ������ ��Ÿ���� Ű����
#define DEFAULT_ATTACK_KEYWORD	TEXT("DefaultAttack")

// ���� Static Mesh ���� �̸�
#define WEAPON_SOCKET_START		TEXT("Socket_SaberStart")
#define WEAPON_SOCKET_END		TEXT("Socket_SaberEnd")




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	// ���� ������ ���̺��� ��Ÿ���ϴ�.
	class UDataTable* DT_AttackData;

	// �ٷ� ������ �����Ų ���� ������ ��Ÿ���ϴ�.
	struct FAttackData* PrevAttackData;

	// ���� �������� ������ ��Ÿ���ϴ�.
	struct FAttackData* CurrentAttackData;

	// ���� ĳ���Ϳ��� ����� ���ݷ�
	float Atk;

	// ���� ������ ������ ��� ���� �����
	float ApplyDamage;

	// ���� ���� Ȱ��ȭ ���¸� ��Ÿ���ϴ�.
	bool IsAttackAreaEnabled;

	// ��� �Է��� ������ �ð��� ��Ÿ���ϴ�.
	float BlockStartTime;

	// ���� �� ������ �� ��ü�� ��� �����ص� �迭
	TArray<class AEnemyCharacter*> AttackDetectedEnemies;

	// ���� �� ������ ���͵��� ��� �����ص� �迭
	TArray<class AActor*> AttackDetectedActors;



	// �Էµ� �޺� ī��Ʈ
	int32 TargetCombo;

	// ������� ����� �޺� ī��Ʈ�� ��Ÿ���ϴ�.
	int32 CurrentCombo;

	// ���� ���� �Է��� Ȯ���ϰ� ������ ��Ÿ���ϴ�.
	bool bCheckingNextAttackInput;

	// ��û�� ���� ť
	TQueue<struct FAttackData*> RequestAttackQueue;

	// �÷��̾� ĳ���� ��ü�� ��Ÿ���ϴ�.
	class AGameCharacter* PlayerCharacter;

	// ���� ���������� ��Ÿ���ϴ�.
	bool IsAttacking;

	// ���� ��������� ��Ÿ���ϴ�.
	bool IsBlocking;

	// ������ ���� ��ġ�� ��Ÿ���ϴ�.
	FVector CurrentSaberStartSocketLocation;
	FVector CurrentSaberEndSocketLocation;

	// ���� ��� �ڵ�
	FName AttackCode;




public:	
	UPlayerCharacterAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// ��ų�� ������� ó���մϴ�.
	void AttackProcedure();

	// ���� ������ Ȯ���մϴ�.
	void CheckAttackArea();

	// â ����� ������ �ϴ��� Ȯ���մϴ�.
	void CheckSpearAttack();

public :
	void UpdateAtk(float atk);

	// ���� ���� ��ġ�� �����մϴ�.
	// weaponMesh : ���� ��ġ�� ���� StaticMesh ������ �����մϴ�.
	void UpdateWeaponSocketLocation(class UStaticMeshComponent* weaponMesh);

	// ���� ������ ���ϴ�.
	void ClearCurrentAttack();

	// ���� ���¸� ����մϴ�.
	void CancelAttackState();

	// ������ ��û�մϴ�.
	void RequestAttack(FName attackName);

	// ���� ���� �Է� Ȯ�� ����
	void StartCheckingNextAttackInput();

	// ���� ���� �Է� Ȯ�� ��
	void FinishCheckingNextAttackInput();

	// ���� ���� Ȱ��ȭ
	void EnableAttackArea();

	// ���� ���� ��Ȱ��ȭ
	void DisableAttackArea();

	// ��� ����
	void OnBlockStarted();

	// ��� ��
	void OnBlockFinished();

	FAttackData* GetAttackData();

	FORCEINLINE bool GetAttackState() const
	{
		return IsAttacking;
	}

	FORCEINLINE bool GetBlockState() const
	{
		return IsBlocking;
	}

	FORCEINLINE float GetBlockStartTime() const
	{
		return BlockStartTime;
	}


};
