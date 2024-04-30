#include "Widget/StoreItemWidget/StoreItemWidget.h"

#include "Components/Button.h"

void UStoreItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


}



void UStoreItemWidget::InitializeWeaponCode(FName weaponCode)
{
	WeaponCode = weaponCode;

}


