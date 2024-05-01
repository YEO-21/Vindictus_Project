#include "Widget/NpcDialogWidget/WalldoNpcWeaponWidget/WalldoNpcWeaponWidget.h"
#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Widget/GameWidget/GameWidget.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerCharacterInteractComponent/PlayerCharacterInteractComponent.h"
#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "Object/InteractionParam/WeaponNpcInteractParam/WeaponNpcInteractParam.h"
#include "../soulproject.h"


void UWalldoNpcWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Ÿ�̸Ӱ� �۵� ���̶�� �ʱ�ȭ�մϴ�.
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
	
	AGameCharacter* gameCharacter = 
		Cast<AGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	UDataTable* weaponData = gameCharacter->GetEquipWeaponComponent()->GetWeaponData();


	Overlay_Parent->AddChild(weaponStoreWidget);
	UOverlaySlot* slot = Cast<UOverlaySlot>(weaponStoreWidget->Slot);
	slot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
	slot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;

	//TArray<FName> items;
	//
	//// ���� �ڵ� �迭
	//TArray<FName> ItemCodes;
	//ItemCodes = weaponData->GetRowNames();
	//
	//for (int i = 0; i < ItemCodes.Num(); ++i)
	//{
	//	items.Add(ItemCodes[i]);
	//}

	// �Ǹ� ������ ���� �ʱ�ȭ
	weaponStoreWidget->InitializeWeaponStoreWidget(interactionParam->SaleItemCodes);
	
}

