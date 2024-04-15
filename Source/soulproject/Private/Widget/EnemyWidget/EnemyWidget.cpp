#include "Widget/EnemyWidget/EnemyWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� �������Ʈ���� ���� �̸��� �̿��Ͽ� ���� ��ü�� ã���ϴ�.
	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
	Progressbar_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progressbar_Hp")));
}

void UEnemyWidget::InitializeEnemyWidget(FText name, float maxHp)
{
	// �ִ� ü�� ����
	MaxHp = maxHp;

	// �̸� �ؽ�Ʈ ����
	Text_Name->SetText(name);

	// ü�� �� �ʱ�ȭ
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
