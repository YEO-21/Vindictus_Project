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

	UPROPERTY()
	class AGameCharacter* OwnerCharacter;


public:
	UAttackNiagaraSystem();

private:
	FVector GetAttackLocation();
	
};
