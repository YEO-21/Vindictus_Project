#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"



void USupplyStoreWidget::InitializeSupplyStoreWidget()
{





}

void USupplyStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư�� �迭�� �߰��մϴ�.
	SupplyItemButtons.Add(Button_Atk);
	SupplyItemButtons.Add(Button_Def);
	SupplyItemButtons.Add(Button_Hp);
	SupplyItemButtons.Add(Button_Critical);

}
