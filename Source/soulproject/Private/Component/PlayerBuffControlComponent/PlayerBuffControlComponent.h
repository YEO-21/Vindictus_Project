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
	// �÷��̾ ���� ȿ���� ��Ÿ���ϴ�.
	//class USupplyNpcInteractParam* Buff;


	// �÷��̾ ���� ȿ���� ��Ÿ���� �迭�Դϴ�.
	//TArray<class USupplyNpcInteractParam*> BuffLists;

	TArray<enum ESupplyItemType> SupplyItemLists;

	//TMap<ESupplyItemType, class USupplyNpcInteractParam> SupplyToBuff;



public:	
	UPlayerBuffControlComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetBuffLists(ESupplyItemType item);
	void RemoveBuff();

	void CheckSupplyItemLists();
		
};
