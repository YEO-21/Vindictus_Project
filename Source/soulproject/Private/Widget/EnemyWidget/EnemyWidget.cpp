#include "Widget/EnemyWidget/EnemyWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 위젯 블루프린트에서 위젯 이름을 이용하여 위젯 객체를 찾습니다.
	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
	Progressbar_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progressbar_Hp")));
}

void UEnemyWidget::InitializeEnemyWidget(FText name, float maxHp)
{
	// 최대 체력 설정
	MaxHp = maxHp;

	// 이름 텍스트 설정
	Text_Name->SetText(name);

	// 체력 값 초기화
	SetHp(MaxHp);

	HideWidget();
}

void UEnemyWidget::SetHp(float newHp)
{
	float hpValue = newHp / MaxHp;
	Progressbar_Hp->SetPercent(hpValue);
}

void UEnemyWidget::ShowWidget()
{
	Text_Name->SetVisibility(ESlateVisibility::Visible);
	Progressbar_Hp->SetVisibility(ESlateVisibility::Visible);
}

void UEnemyWidget::HideWidget()
{
	Text_Name->SetVisibility(ESlateVisibility::Hidden);
	Progressbar_Hp->SetVisibility(ESlateVisibility::Hidden);
}
