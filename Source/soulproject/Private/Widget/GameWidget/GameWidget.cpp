#include "Widget/GameWidget/GameWidget.h"
#include "Widget/PlayerStateWidget/PlayerStateWidget.h"
#include "Widget/EnemyStateWidget/EnemyStateWidget.h"

#include "Actor/EnemyCharacter/EnemyCharacter.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Overlay_Player = Cast<UOverlay>(GetWidgetFromName(TEXT("Overlay_Player")));
	Overlay_Additive = Cast<UOverlay>(GetWidgetFromName(TEXT("Overlay_Additive")));
	PlayerStateWidget = Cast<UPlayerStateWidget>(GetWidgetFromName(TEXT("PlayerStateWidget")));
	EnemyStateWidget = Cast<UEnemyStateWidget>(GetWidgetFromName(TEXT("EnemyStateWidget")));

	// 적 상태 위젯을 숨깁니다.
	HideEnemyState();
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

	//widgetForClose->RemoveFromParent();
	Overlay_Additive->RemoveChild(widgetForClose);
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
