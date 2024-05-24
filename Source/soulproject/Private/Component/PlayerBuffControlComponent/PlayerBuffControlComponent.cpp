#include "Component/PlayerBuffControlComponent/PlayerBuffControlComponent.h"

#include "Enum/SupplyItem/SupplyItemType.h"

UPlayerBuffControlComponent::UPlayerBuffControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerBuffControlComponent::BeginPlay()
{
	Super::BeginPlay();

	
	//SupplyToBuff.Add(ESupplyItemType::AtkBase, &USupplyNpcInteractParam)

}


void UPlayerBuffControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerBuffControlComponent::SetBuffLists(ESupplyItemType item)
{
	switch (item)
	{
	case ESupplyItemType::AtkBase:
		{
			
		}
		break;
	case ESupplyItemType::DefBase:
		{

		}
		break;
	case ESupplyItemType::HpBase:
		{

		}
		break;
	case ESupplyItemType::CriticalBase:
		{

		}
		break;
	}
	


}

void UPlayerBuffControlComponent::CheckSupplyItemLists()
{
	for (enum ESupplyItemType itemType : SupplyItemLists)
	{
		SetBuffLists(itemType);
	}



}

