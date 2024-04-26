#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"

#include "Components/Button.h"

void UWeaponStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Buy->OnClicked.AddDynamic(this, &ThisClass::OnButtonBuyClicked);

}

void UWeaponStoreWidget::OnButtonBuyClicked()
{
	WeaponBuyEvent.Broadcast();
}


