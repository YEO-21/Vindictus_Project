#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Object/InteractionParam/InteractionParamBase.h"
#include "Structure/NpcData/NpcData.h"


void UNpcDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Overlay_Parent = Cast<UOverlay>(GetWidgetFromName(TEXT("Overlay_Parent")));
	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
	Text_Dialog = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Dialog")));
	Button_Close = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));

	Button_Close->OnClicked.AddDynamic(this, &ThisClass::OnCloseButtonClicked);

	// 위젯 애니메이션 재생
	PlayAnimation(FadeInAnimation);
}

void UNpcDialogWidget::InitializeNpcDialogWidget(FNpcData* npcData, FOnDialogCloseEventSignature onDialogClosed, UInteractionParamBase* interactionParam)
{
	UIInteractionParam = interactionParam;

	Text_Name->SetText(npcData->Name);
	Text_Dialog->SetText(npcData->DialogText);

	OnDialogClosed = onDialogClosed;
}

UInteractionParamBase* UNpcDialogWidget::GetInteractionParam()
{
	return UIInteractionParam;
}


void UNpcDialogWidget::OnCloseButtonClicked()
{
	OnDialogClosed.Broadcast();
}

void UNpcDialogWidget::HideDialogWidget()
{
	Text_Name->SetVisibility(ESlateVisibility::Hidden);
	Text_Dialog->SetVisibility(ESlateVisibility::Hidden);
	//Button_Close->SetVisibility(ESlateVisibility::Hidden);
}
