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
	// ���� ����� ���� �������� Ÿ���� ��Ÿ���ϴ�.
	enum ESupplyItemType SupplyItem;

	// �����ų �������� ���� ť�Դϴ�.
	TQueue<enum ESupplyItemType> SupplyItemList;
	
	// ����� ������ ��� �迭�Դϴ�.
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
