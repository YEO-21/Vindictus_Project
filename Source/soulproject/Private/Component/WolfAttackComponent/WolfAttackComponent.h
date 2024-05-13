// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WolfAttackComponent.generated.h"


#define WOLF_SOCKET_START		TEXT("Socket_AttackStart")
#define WOLF_SOCKET_END			TEXT("Socket_AttackEnd")


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UWolfAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	class UAnimMontage* AttackAnimMontage;



public:	
	UWolfAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	void Attack();

private:
	void CheckAttackArea();
		
};
