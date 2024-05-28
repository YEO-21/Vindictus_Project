// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/SupplyItem/SupplyItemType.h"
#include "Components/ActorComponent.h"
#include "PlayerBuffControlComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerBuffControlComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	// 현재 적용된 지원 아이템의 타입을 나타냅니다.
	enum ESupplyItemType SupplyItem;

	// 적용시킬 버프들을 담을 큐입니다.
	TQueue<enum ESupplyItemType> SupplyItemList;
	
	// 적용된 버프를 담는 배열입니다.
	TArray<enum ESupplyItemType> CurrentBuffs;

	class USupplyNpcInteractParam* AttackSupply;
	class USupplyNpcInteractParam* DefenceSupply;
	class USupplyNpcInteractParam* HpSupply;
	class USupplyNpcInteractParam* CriticalAttackSupply;

public:
	UPlayerBuffControlComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
public:
	void ApplySupplyItem();

	void CheckCurrentBuff(ESupplyItemType itemType);

};
