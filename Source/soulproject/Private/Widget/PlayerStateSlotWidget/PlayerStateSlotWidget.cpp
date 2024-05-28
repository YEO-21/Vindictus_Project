#include "Widget/PlayerStateSlotWidget/PlayerStateSlotWidget.h"
#include "Widget/SupplyItemGridWidget/SupplyItemGridWidget.h"
#include "Enum/SupplyItem/SupplyItemType.h"

#include "Components/Image.h"

void UPlayerStateSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UPlayerStateSlotWidget::SetImageMaterial(ESupplyItemType itemType, UMaterialInterface* material)
{
	switch (itemType)
	{
	case ESupplyItemType::AtkBase:
	{
		Slot_Atk->SetBrushFromMaterial(material);
	}
	break;
	case ESupplyItemType::DefBase:
	{
		Slot_Def->SetBrushFromMaterial(material);
	}
	break;
	case ESupplyItemType::HpBase:
	{
		Slot_Hp->SetBrushFromMaterial(material);
	}
	break;
	case ESupplyItemType::CriticalBase:
	{
		Slot_Critical->SetBrushFromMaterial(material);
	}
	break;
	}
}


