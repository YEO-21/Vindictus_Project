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

	// 늑대 그룹을 나타냅니다.
	UPROPERTY()
	TArray<AWolfCharacter*> Group;

	UPROPERTY()
	class UAnimMontage* HitAnimMontage;

public :
	AWolfCharacter();

protected :
	virtual void BeginPlay() override;

public :
	virtual void Tick(float dt) override;

private :
	// 애님 인스턴스 파라미터 갱신
	void UpdateAnimInstanceParams();

	// 그룹을 찾습니다.
	void FindGroup();

	// 늑대 상태를 결정하기 위한 수를 뽑습니다.
	UFUNCTION(BlueprintCallable)
	void GetWolfStateNumber();

protected :
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage) override;

public :
	// 공격 컴포넌트를 얻습니다.
	FORCEINLINE class UWolfAttackComponent* GetAttackComponent() const
	{ return AttackComponent; }


	
};
