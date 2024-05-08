// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

#define BLACKBOARDKEY_SPAWNLOCATION			TEXT("SpawnLocation")
#define BLACKBOARDKEY_ISAGGRESSIVESTATE		TEXT("IsAggressiveState")
#define BLACKBOARDKEY_LASTDAMAGEDTIME		TEXT("LastDamagedTime")
#define BLACKBOARDKEY_TIMETOCALMDOWN		TEXT("TimeToCalmDown")
#define BLACKBOARDKEY_ISDEAD				TEXT("IsDead")
#define BLACKBOARDKEY_MAXMOVEDISTANCE		TEXT("MaxMoveDistance")
#define BLACKBOARDKEY_DAMAGEACTOR			TEXT("DamageActor")
#define BLACKBOARDKEY_PLAYERCHARACTER		TEXT("PlayerCharacter")
#define BLACKBOARDKEY_ISPLAYERDEAD			TEXT("IsPlayerDead")
#define BLACKBOARDKEY_ISATTACKING			TEXT("IsAttacking")

/**
 * �� ĳ���Ϳ��� �⺻������ ����ϴ� ��Ʈ�ѷ��Դϴ�.
 */
UCLASS()
class AEnemyController : public AAIController
{
	GENERATED_BODY()

protected :
	// ���Ǵ� BlackboardComponent �� ��Ÿ���ϴ�.
	UPROPERTY()
	class UBlackboardComponent * BlackBoardComponent;

private:
	// �÷��̾� ĳ���� ������
	struct FPlayerCharacterData* PlayerCharacterData;

protected :
	// ��Ʈ�ѷ��� Pawn �� ���ǵǾ��� ��� ȣ��Ǵ� �Լ��Դϴ�.
	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnBlackboardKeyInitialize(class UBlackboardComponent* blackboardComponent, class APawn* inPawn);

public :

	virtual void InitializeEnemyController(struct FEnemyData* enemyData);

	// �����ϴ� ���� ���ظ� �Ծ��� ��� ȣ��Ǵ� �Լ��Դϴ�.
	// gameCharacter : ���ظ� ���� ���Ͱ� ���޵˴ϴ�.
	// damage : ���� ���ط��� ���Ǿ� ���޵˴ϴ�.
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage);

	// �����ϴ� ���� ����� ��� ȣ��Ǵ� �޼����Դϴ�.
	virtual void OnDead();
	
	// �÷��̾� ĳ���Ͱ� ����� ��� ȣ��Ǵ� �޼����Դϴ�.
	virtual void OnPlayerDead();

	// �÷��̾� ĳ���Ͱ� �������� ��� ȣ��Ǵ� �޼����Դϴ�.
	virtual void OnPlayerRespawn();
};
