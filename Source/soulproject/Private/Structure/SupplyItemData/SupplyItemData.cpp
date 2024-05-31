#include "SupplyItemData.h"

FSupplyItemData::FSupplyItemData()
{
	BuffName = TEXT("");

	BuffImage = nullptr;
	BuffPrice = PersistTime = 0.0f;
	ItemType = ESupplyItemType::AtkBase;
	ItemEffect = FText::FromString(TEXT(""));


}
