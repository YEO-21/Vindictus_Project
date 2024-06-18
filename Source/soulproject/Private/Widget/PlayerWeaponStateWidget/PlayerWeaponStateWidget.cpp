#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"
#include "Components/Image.h"

void UPlayerWeaponStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWeaponStateTexture.BindUObject(this, &UPlayerWeaponStateWidget::SetMainWeaponImage);
}




FUpdateTextureEventSignature UPlayerWeaponStateWidget::GetWeaponStateEvent() const
{
	return UpdateWeaponStateTexture;
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

void UPlayerWeaponStateWidget::SetMainWeaponImage(UTexture2D* texture)
{
	MainWeapon->SetBrushFromTexture(texture);
	UE_LOG(LogTemp, Warning, TEXT("SetMainWeaponImage is Called"));
}
