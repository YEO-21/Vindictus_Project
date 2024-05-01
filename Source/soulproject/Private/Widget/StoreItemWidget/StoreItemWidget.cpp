#include "Widget/StoreItemWidget/StoreItemWidget.h"

#include "Components/Button.h"

void UStoreItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Buy->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonBuyClicked);
	//Image_Weapon = 
}

void UStoreItemWidget::InitializeStoreWidget(WeaponBuyButtonClickSignature weaponBuyEvent)
{
	WeaponBuyEvent = weaponBuyEvent;
}


void UStoreItemWidget::OnButtonBuyClicked()
{
	WeaponBuyEvent.Broadcast(WeaponCode);

}


