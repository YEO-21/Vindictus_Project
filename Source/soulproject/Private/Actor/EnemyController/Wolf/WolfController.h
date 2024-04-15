// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyController/EnemyController.h"
#include "WolfController.generated.h"

#define BLACKBOARDKEY_ISATTACKING		TEXT("IsAttacking")

/**
 * 
 */
UCLASS()
class AWolfController : public AEnemyController
{
	GENERATED_BODY()


protected :
	virtual void OnBlackboardKeyInitialize(class UBlackboardComponent* blackboardComponent, class APawn* inPawn) override;
	

public :
	void Attack();
	void OnAttackFinished();

	// �ٸ� ���� ĳ���Ͱ� ���ݹ޾��� �� ȣ��˴ϴ�.
	void OnOtherWolfDamaged(class AGameCharacter* gameCharacter);
};
