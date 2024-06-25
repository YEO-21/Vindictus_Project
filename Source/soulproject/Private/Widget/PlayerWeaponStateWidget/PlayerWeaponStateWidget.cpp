#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"






void UPlayerWeaponStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 시작 포션 개수 설정
	PortionCount = PORTION_COUNT;
	
	SetPortionCount(PortionCount);

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
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
	UE_LOG(LogTemp, Warning, TEXT("%s"), *texture->GetFName().ToString());
}

void UPlayerWeaponStateWidget::ReducePortionCount()
{
	--PortionCount;
	if (PortionCount < 0) PortionCount = 0;

	SetPortionCount(PortionCount);

	// 위젯 애니메이션 재생
	PlayAnimation(ConsumeHp);
}

void UPlayerWeaponStateWidget::SetPortionCount(int32 count)
{
	PortionCount = count;

	FText fromInt = FText::FromString(FString::Printf(TEXT("%d"), count));
	TextBlock_PortionCount->SetText(fromInt);
}
