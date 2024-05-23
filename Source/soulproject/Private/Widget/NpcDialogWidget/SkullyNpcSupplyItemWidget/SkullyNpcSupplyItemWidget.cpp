#include "Widget/NpcDialogWidget/SkullyNpcSupplyItemWidget/SkullyNpcSupplyItemWidget.h"
#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"
#include "Widget/GameWidget/GameWidget.h"
#include "Widget/SupplyItemGridWidget/SupplyItemGridWidget.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Object/InteractionParam/SupplyNpcInteractParam/SupplyNpcInteractParam.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

#include "Components/Button.h"
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
	USupplyItemGridWidget* supplyStoreWidget = CreateWidget<USupplyItemGridWidget>(this, interactionParam->BP_SupplyStoreWidgetClass);

	AGamePlayerController* playerController =
		Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());

	if (!IsValid(playerController)) return;
	

	Overlay_Parent->AddChild(supplyStoreWidget);
	UOverlaySlot* slot = Cast<UOverlaySlot>(supplyStoreWidget->Slot);
	slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	// Áö¿ø ¾ÆÀÌÅÛ À§Á¬ ÃÊ±âÈ­
	supplyStoreWidget->InitializeSupplyStoreWidget();

	//// ´ëÈ­ À§Á¬ ¼û±è
	HideDialogWidget();

	// ¹«±â »óÅÂ À§Á¬ ¼û±è
	playerController->GetGameWidget()->HideWeaponWidget();


}
