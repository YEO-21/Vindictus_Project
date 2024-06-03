// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "AttackNiagaraSystem.generated.h"

/**
 * 
 */
UCLASS()
class UAttackNiagaraSystem : public UNiagaraSystem
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* HitNiagaraComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UNiagaraScript* NiagaraSystemScript;


	UPROPERTY()
	class AGameCharacter* OwnerCharacter;


public:
	UAttackNiagaraSystem();

private:
	FVector GetAttackLocation();

public:
	void ActivateNiagaraSystem();

	void SetNiagaraSystemLocation(FVector location, FVector hitLocation);
	void SetNiagaraSystemAsset(UNiagaraSystem* effect, UNiagaraSystem* hiteffect);
	
};
