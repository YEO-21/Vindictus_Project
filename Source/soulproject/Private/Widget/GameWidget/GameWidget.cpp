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
	

	// �� ���� ������ ����ϴ�.
	HideEnemyState();

	// ��� ���� ������ ����ϴ�.

	HideDeadWidget();

	// ũ��Ƽ�� ������ ����ϴ�.
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
	// Overlay_Additive ������ �߰��մϴ�.
	Overlay_Additive->AddChild(widgetInstance);

	// ������ ������ ���� ������ ����ϴ�.
	UOverlaySlot* widgetSlot = Cast<UOverlaySlot>(widgetInstance->Slot);

	// ���� ȭ�� ä���
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
	// Overlay_PlayerState ������ ������ �߰��մϴ�.
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

	// ������ ǥ���մϴ�.
	EnemyStateWidget->SetVisibility(ESlateVisibility::Visible);

	// �� ����
	EnemyStateWidget->UpdateTargetEnemy(newTargetEnemy);

	// ������ ����� �ð��� �����մϴ�.
	EnemyStateWidgetFloatingTime = GetWorld()->GetTimeSeconds();
}

void UGameWidget::HideEnemyState()
{
	// ������ ǥ������ �ʽ��ϴ�.
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

