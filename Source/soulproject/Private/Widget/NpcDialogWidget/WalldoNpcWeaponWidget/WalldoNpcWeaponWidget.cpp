#include "Widget/NpcDialogWidget/WalldoNpcWeaponWidget/WalldoNpcWeaponWidget.h"
#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Widget/GameWidget/GameWidget.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerCharacterInteractComponent/PlayerCharacterInteractComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "Object/InteractionParam/WeaponNpcInteractParam/WeaponNpcInteractParam.h"
#include "../soulproject.h"


void UWalldoNpcWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	

	
	// 타이머가 작동 중이라면 초기화합니다.
	//if (WeaponStoreShowTimerHandle.IsValid()) 

	FTimerDelegate timerDelegate;
	timerDelegate.BindUObject(this, &ThisClass::CreateWeaponWidget);

	GetOwningPlayer()->GetWorldTimerManager().SetTimer(WeaponStoreShowTimerHandle,
		timerDelegate, 3.0f, false);
}

void UWalldoNpcWeaponWidget::CreateWeaponWidget()
{

	UWeaponNpcInteractParam* interactionParam = Cast<UWeaponNpcInteractParam>(UIInteractionParam);
	UWeaponStoreWidget* weaponStoreWidget = CreateWidget<UWeaponStoreWidget>(this, interactionParam->BP_WeaponStoreWidgetClass);
	
	Overlay_Parent->AddChild(weaponStoreWidget);
	UOverlaySlot* slot = Cast<UOverlaySlot>(weaponStoreWidget->Slot);
	slot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
	slot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
		
	//HideDialogGameWidget();

}

void UWalldoNpcWeaponWidget::HideDialogGameWidget()
{
	AGamePlayerController* playerController = Cast<AGamePlayerController>(GetOwningPlayer());
	

	// GameWidget 
	//playerController->GetGameWidget()->SetRenderOpacity(0.5f);


	// DialogWidget 숨기기
	//npcDialogWidget->SetVisibility(ESlateVisibility::Hidden);


}
