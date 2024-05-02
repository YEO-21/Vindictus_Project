#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"
#include "Components/Image.h"

void UPlayerWeaponStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	

}

void UPlayerWeaponStateWidget::ExchangeWeaponWidget()
{
	FSlateBrush mainWeaponBrush = MainWeapon->GetBrush();
	FSlateBrush subWeaponBrush = SubWeapon->GetBrush();

	MainWeapon->SetBrush(subWeaponBrush);
	SubWeapon->SetBrush(mainWeaponBrush);

	
	

}

void UPlayerWeaponStateWidget::HideWeaponStateWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWeaponStateWidget::ShowWeaponStateWidget()
{
	SetVisibility(ESlateVisibility::Visible);
}
