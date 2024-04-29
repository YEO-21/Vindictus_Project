#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"

#include "Components/Button.h"

void UWeaponStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Buy->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonBuyClicked);

}

void UWeaponStoreWidget::InitializeWeaponStoreWidget(WeaponBuyButtonClickSignature weaponStoreWidgetEvent)
{
	WeaponBuyEvent = weaponStoreWidgetEvent;
}

void UWeaponStoreWidget::OnButtonBuyClicked()
{
	WeaponBuyEvent.Broadcast();
}


