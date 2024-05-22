#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"



void USupplyStoreWidget::InitializeSupplyStoreWidget()
{





}

void USupplyStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼을 배열에 추가합니다.
	SupplyItemButtons.Add(Button_Atk);
	SupplyItemButtons.Add(Button_Def);
	SupplyItemButtons.Add(Button_Hp);
	SupplyItemButtons.Add(Button_Critical);

}
