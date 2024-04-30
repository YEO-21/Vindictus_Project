#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Widget/StoreItemWidget/StoreItemWidget.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

UWeaponStoreWidget::UWeaponStoreWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UStoreItemWidget> WIDGETBP_STOREITEMCLASS(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/WeaponStoreWidget/WidgetBP_StoreItem.WidgetBP_StoreItem_C'"));

	if (WIDGETBP_STOREITEMCLASS.Succeeded())
		WidgetBP_StoreItemClass = WIDGETBP_STOREITEMCLASS.Class;
}

void UWeaponStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemGridPanel = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("ItemGridPanel")));

	Button_Buy->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonBuyClicked);

	
}

void UWeaponStoreWidget::InitializeWeaponStoreWidget(WeaponBuyButtonClickSignature weaponStoreWidgetEvent)
{
	WeaponBuyEvent = weaponStoreWidgetEvent;
}

void UWeaponStoreWidget::InitializeWeaponStoreWidget(TArray<FName> itemCodes)
{
	for (FName itemCode : itemCodes)
	{
		UStoreItemWidget* createdStoreItemWidget = CreateWidget<UStoreItemWidget>(this, WidgetBP_StoreItemClass);
		ItemGridPanel->AddChild(createdStoreItemWidget);
		UUniformGridSlot* slot = Cast<UUniformGridSlot>(createdStoreItemWidget->Slot);

		slot->SetColumn();
		slot->SetRow();

		createdStoreItemWidget->WeaponCode = itemCode;
		// 이벤트 바인딩ㄴ
	}

}

void UWeaponStoreWidget::InitializeItemNameWidget(GetItemNameSignature itemName)
{
	GetItemName = itemName;
}

void UWeaponStoreWidget::OnButtonBuyClicked()
{
	if (GetItemName.IsBound()) WeaponBuyEvent.Broadcast(GetItemName.Execute());

	
	// Get PlayerController
	//AGamePlayerController* playerController = 
	//	Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());

	//// Get PlayerCharacter
	//AGameCharacter* playerCharacter = Cast<AGameCharacter>(playerController->GetPawn());

	//if (!IsValid(playerCharacter)) return;

	//playerCharacter->EquippedWeaponCode = TEXT("000003");
	
	



}




