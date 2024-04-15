// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "WolfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AWolfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere)
	class UWolfAttackComponent* AttackComponent;

	// ���� �׷��� ��Ÿ���ϴ�.
	UPROPERTY()
	TArray<AWolfCharacter*> Group;

public :
	AWolfCharacter();

protected :
	virtual void BeginPlay() override;

public :
	virtual void Tick(float dt) override;

private :
	// �ִ� �ν��Ͻ� �Ķ���� ����
	void UpdateAnimInstanceParams();

	// �׷��� ã���ϴ�.
	void FindGroup();

protected :
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage) override;

public :
	// ���� ������Ʈ�� ����ϴ�.
	FORCEINLINE class UWolfAttackComponent* GetAttackComponent() const
	{ return AttackComponent; }


	
};
