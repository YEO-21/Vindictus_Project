#include "Widget/NpcDialogWidget/SkullyNpcSupplyItemWidget/SkullyNpcSupplyItemWidget.h"
#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"

#include "Object/InteractionParam/SupplyNpcInteractParam/SupplyNpcInteractParam.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

#include "TimerManager.h"

void USkullyNpcSupplyItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerDelegate timerDelegate;
	timerDelegate.BindUObject(this, &ThisClass::CreateSupplyItemWidget);

	GetOwningPlayer()->GetWorldTimerManager().SetTimer(SupplyStoreShowTimerHandle,
		timerDelegate, 3.0f, false);


}

void USkullyNpcSupplyItemWidget::CreateSupplyItemWidget()
{
	USupplyNpcInteractParam* interactionParam = Cast<USupplyNpcInteractParam>(UIInteractionParam);
	USupplyStoreWidget* supplyStoreWidget = CreateWidget<USupplyStoreWidget>(this, interactionParam->BP_SupplyStoreWidgetClass);

	
	supplyStoreWidget->AddToViewport();

	Overlay_Child->AddChild(supplyStoreWidget);
	//UOverlaySlot* slot = Cast<UOverlaySlot>(supplyStoreWidget->Slot);
	//slot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
	//slot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;







	HideDialogWidget();

	
}
