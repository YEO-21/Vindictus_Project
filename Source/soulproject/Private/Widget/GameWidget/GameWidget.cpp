#include "Widget/GameWidget/GameWidget.h"
#include "Widget/PlayerStateWidget/PlayerStateWidget.h"
#include "Widget/EnemyStateWidget/EnemyStateWidget.h"
#include "Widget/PlayerStateSlotWidget/PlayerStateSlotWidget.h"

#include "Actor/EnemyCharacter/EnemyCharacter.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Overlay_Player = Cast<UOverlay>(GetWidgetFromName(TEXT("Overlay_Player")));
	Overlay_Additive = Cast<UOverlay>(GetWidgetFromName(TEXT("Overlay_Additive")));
	PlayerStateWidget = Cast<UPlayerStateWidget>(GetWidgetFromName(TEXT("PlayerStateWidget")));
	EnemyStateWidget = Cast<UEnemyStateWidget>(GetWidgetFromName(TEXT("EnemyStateWidget")));
	TextBlock_Dead = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Dead")));
	CriticalAttackWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("CriticalAttackWidget")));
	PlayerStateSlotWidget = Cast<UPlayerStateSlotWidget>(GetWidgetFromName(TEXT("PlayerStateSlotWidget")));
	

	// 적 상태 위젯을 숨깁니다.
	HideEnemyState();

	// 사망 상태 위젯을 숨깁니다.

	HideDeadWidget();

	// 크리티컬 위젯을 숨깁니다.
	HideCriticalWidget();
}

void UGameWidget::NativeTick(const FGeometry& myGeometry, float dt)
{
	Super::NativeTick(myGeometry, dt);

	if (GetWorld()->GetTimeSeconds() > EnemyStateWidgetFloatingTime + 5.0f)
	{
		HideEnemyState();
	}
}

void UGameWidget::FloatingWidgetAdditive(UUserWidget* widgetInstance)
{
	// Overlay_Additive 하위로 추가합니다.
	Overlay_Additive->AddChild(widgetInstance);

	// 생성된 위젯에 대한 슬롯을 얻습니다.
	UOverlaySlot* widgetSlot = Cast<UOverlaySlot>(widgetInstance->Slot);

	// 위젯 화면 채우기
	widgetSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	widgetSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
}

void UGameWidget::RemoveWidgetAdditive(UUserWidget* widgetForClose)
{

	widgetForClose->RemoveFromParent();
	//Overlay_Additive->RemoveChild(widgetForClose);
}

void UGameWidget::FloatingWidgetPlayerState(UUserWidget* widgetInstance)
{
	// Overlay_PlayerState 하위로 위젯을 추가합니다.
	Overlay_PlayerState->AddChild(widgetInstance);




}

UPlayerStateWidget* UGameWidget::GetPlayerStateWidget() const
{
	return PlayerStateWidget;
}

void UGameWidget::ShowEnemyState(AEnemyCharacter* newTargetEnemy)
{
	if (!IsValid(EnemyStateWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is not Valid"));
		return;
	}

	// 위젯을 표시합니다.
	EnemyStateWidget->SetVisibility(ESlateVisibility::Visible);

	// 적 설정
	EnemyStateWidget->UpdateTargetEnemy(newTargetEnemy);

	// 위젯이 띄워진 시간을 저장합니다.
	EnemyStateWidgetFloatingTime = GetWorld()->GetTimeSeconds();
}

void UGameWidget::HideEnemyState()
{
	// 위젯을 표시하지 않습니다.
	EnemyStateWidget->SetVisibility(ESlateVisibility::Collapsed);

	

}

void UGameWidget::ShowDeadWidget()
{
	TextBlock_Dead->SetVisibility(ESlateVisibility::Visible);

	PlayAnimation(TextBlock_Dead_Animation);
}

void UGameWidget::HideDeadWidget()
{
	TextBlock_Dead->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameWidget::ShowWeaponWidget()
{
	Overlay_Weapon->SetVisibility(ESlateVisibility::Visible);
}

void UGameWidget::ShowCriticalWidget()
{
	CriticalAttackWidget->SetVisibility(ESlateVisibility::Visible);
}

void UGameWidget::HideCriticalWidget()
{
	CriticalAttackWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UGameWidget::ShowPlayerStateWidget()
{
	Overlay_PlayerState->SetVisibility(ESlateVisibility::Visible);
}

void UGameWidget::HidePlayerStateWidget()
{
	Overlay_PlayerState->SetVisibility(ESlateVisibility::Hidden);
}

void UGameWidget::HideAllWidget()
{
	Overlay_All->SetVisibility(ESlateVisibility::Hidden);
}

void UGameWidget::ShowAllWidget()
{
	Overlay_All->SetVisibility(ESlateVisibility::Visible);
}

void UGameWidget::InitializePlayerStateSlotWidget(UPlayerStateSlotWidget* playerSlotWidget)
{
	PlayerStateSlotWidget = playerSlotWidget;
}

void UGameWidget::HideWeaponWidget()
{
	Overlay_Weapon->SetVisibility(ESlateVisibility::Hidden);
}

