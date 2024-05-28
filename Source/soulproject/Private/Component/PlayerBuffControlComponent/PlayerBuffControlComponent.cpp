#include "Component/PlayerBuffControlComponent/PlayerBuffControlComponent.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "Widget/PlayerStateSlotWidget/PlayerStateSlotWidget.h"

#include "Enum/SupplyItem/SupplyItemType.h"

#include "Object/InteractionParam/InteractionParamBase.h"
#include "Object/InteractionParam/SupplyNpcInteractParam/SupplyNpcInteractParam.h"

UPlayerBuffControlComponent::UPlayerBuffControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerBuffControlComponent::BeginPlay()
{
	Super::BeginPlay();

	AttackSupply = NewObject<USupplyNpcInteractParam>(this);
	DefenceSupply = NewObject<USupplyNpcInteractParam>(this);
	HpSupply = NewObject<USupplyNpcInteractParam>(this);
	CriticalAttackSupply = NewObject<USupplyNpcInteractParam>(this);
}


void UPlayerBuffControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplySupplyItem();
}

void UPlayerBuffControlComponent::ApplySupplyItem()
{
	if (SupplyItemList.IsEmpty()) return;
	
	SupplyItemList.Dequeue(SupplyItem);
	CheckCurrentBuff(SupplyItem);
}

void UPlayerBuffControlComponent::CheckCurrentBuff(ESupplyItemType itemType)
{
	AGamePlayerController* playerController =
		Cast<AGamePlayerController>(Cast<AGameCharacter>(GetOwner())->GetController());


	switch (itemType)
	{
	case ESupplyItemType::AtkBase:
	{
		AttackSupply->bIsEnable = true;
		playerController->SupplyInteractionItems.Add(AttackSupply);
	}
	break;
	case ESupplyItemType::DefBase:
	{
		DefenceSupply->bIsEnable = true;
		playerController->SupplyInteractionItems.Add(DefenceSupply);
	}
	break;
	case ESupplyItemType::HpBase:
	{
		HpSupply->bIsEnable = true;
		playerController->SupplyInteractionItems.Add(HpSupply);
	}
	break;
	case ESupplyItemType::CriticalBase:
	{
		CriticalAttackSupply->bIsEnable = true;
		playerController->SupplyInteractionItems.Add(CriticalAttackSupply);
	}
	break;
	}

}

