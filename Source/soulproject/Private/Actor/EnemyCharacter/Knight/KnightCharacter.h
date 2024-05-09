// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AKnightCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UKnightAttackComponent * AttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SwordMeshComponent;

	UPROPERTY();
	class UStaticMesh* SwordMesh;

	UPROPERTY();
	class UAnimMontage* HitAnimMontage;
	


public :
	AKnightCharacter();

protected :
	virtual void BeginPlay() override;

public :
	virtual void Tick(float dt) override;

private :
	// 애님 인스턴스 파라미터 갱신
	void UpdateAnimInstanceParams();


protected :
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage) override;

public :
	// 공격 컴포넌트를 반환합니다.
	FORCEINLINE class UKnightAttackComponent* GetAttackComponent()
	{
		return AttackComponent;
	}

};
