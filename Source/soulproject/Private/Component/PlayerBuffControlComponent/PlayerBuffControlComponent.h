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
	// 플레이어가 받을 효과를 나타냅니다.
	//class USupplyNpcInteractParam* Buff;


	// 플레이어가 받은 효과를 나타내는 배열입니다.
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
