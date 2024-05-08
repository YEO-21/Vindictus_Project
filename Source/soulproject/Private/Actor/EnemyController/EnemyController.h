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
 * 적 캐릭터에서 기본적으로 사용하는 컨트롤러입니다.
 */
UCLASS()
class AEnemyController : public AAIController
{
	GENERATED_BODY()

protected :
	// 사용되는 BlackboardComponent 를 나타냅니다.
	UPROPERTY()
	class UBlackboardComponent * BlackBoardComponent;

private:
	// 플레이어 캐릭터 데이터
	struct FPlayerCharacterData* PlayerCharacterData;

protected :
	// 컨트롤러가 Pawn 에 빙의되었을 경우 호출되는 함수입니다.
	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnBlackboardKeyInitialize(class UBlackboardComponent* blackboardComponent, class APawn* inPawn);

public :

	virtual void InitializeEnemyController(struct FEnemyData* enemyData);

	// 조종하는 폰이 피해를 입었을 경우 호출되는 함수입니다.
	// gameCharacter : 피해를 입힌 액터가 전달됩니다.
	// damage : 입은 피해량이 계산되어 전달됩니다.
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage);

	// 조종하는 적이 사망한 경우 호출되는 메서드입니다.
	virtual void OnDead();
	
	// 플레이어 캐릭터가 사망한 경우 호출되는 메서드입니다.
	virtual void OnPlayerDead();

	// 플레이어 캐릭터가 리스폰한 경우 호출되는 메서드입니다.
	virtual void OnPlayerRespawn();
};
