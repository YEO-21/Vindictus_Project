#include "Widget/PlayerStateWidget/PlayerStateWidget.h"
#include "Components/ProgressBar.h"

void UPlayerStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Progressbar_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progressbar_Hp")));
	Progressbar_Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progressbar_Stamina")));

	Progressbar_Hp->PercentDelegate.BindUFunction(this, TEXT("GetHpPercent"));
	Progressbar_Hp->SynchronizeProperties(); // ���� �Ӽ����� ����ȭ ��ŵ�ϴ�.

	Progressbar_Stamina->PercentDelegate.BindUFunction(this, TEXT("GetStaminaPercent"));
	Progressbar_Stamina->SynchronizeProperties();
}

float UPlayerStateWidget::GetHpPercent() const
{
	return CurrentHp / MaxHp;
}

float UPlayerStateWidget::GetStaminaPercent() const
{
	return CurrentStamina / MaxStamina;
}
