#include "Widget/SupplyItemGridWidget/SupplyItemGridWidget.h"
#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"
#include "Widget/PlayerStateSlotWidget/PlayerStateSlotWidget.h"
#include "Widget/GameWidget/GameWidget.h"

#include "Structure/SupplyItemData/SupplyItemData.h"

#include "Component/PlayerBuffControlComponent/PlayerBuffControlComponent.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

USupplyItemGridWidget::USupplyItemGridWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<USupplyStoreWidget> WIDGETBP_SUPPLY(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/SkullyStoreWidget/WidgetBP_SupplyItem.WidgetBP_SupplyItem_C'"));


	if (WIDGETBP_SUPPLY.Succeeded()) WidgetBP_SkullyStore = WIDGETBP_SUPPLY.Class;



}

void USupplyItemGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ������ �ڵ带 �迭�� �߰��մϴ�.
	itemCodes.Add(ATK);
	itemCodes.Add(DEF);
	itemCodes.Add(HP);
	itemCodes.Add(CRITICAL);
}

void USupplyItemGridWidget::InitializeSupplyStoreWidget()
{
	int32 col = 0;
	int32 row = 0;

	// Get GameCharacter
	AGameCharacter* gameCharacter =
		Cast<AGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	AGamePlayerController* playerController =
		Cast<AGamePlayerController>(gameCharacter->GetController());

	
	for (FName itemCode : itemCodes)
	{
		// ������ ������ �����մϴ�.
		USupplyStoreWidget* supplyStoreWidget = CreateWidget<USupplyStoreWidget>(this, WidgetBP_SkullyStore);

		// ������ �ڵ� ������ �ʱ�ȭ�մϴ�.
		supplyStoreWidget->InitializeItemCode(itemCode);

		FSupplyItemData* supplyItemData = supplyStoreWidget->PlayerSupplyData;

		// ������ ������ �̹����� �����մϴ�.
		supplyStoreWidget->SetImageMaterial(supplyItemData->BuffImage);

		// ������ ������ �ؽ�Ʈ�� �����մϴ�.
		supplyStoreWidget->SetText(supplyItemData->ItemEffect);

		// �׸��� �гο� ������ �߰��մϴ�.
		ItemGridPanel->AddChild(supplyStoreWidget);


		SupplyItemBuyButtonClickSignature supplyItemBuyEvent;
		supplyItemBuyEvent.AddLambda([supplyItemData, gameCharacter, playerController, itemCode]()
			{
				gameCharacter->GetBuffControlComponent()->SupplyItemList.Enqueue(supplyItemData->ItemType);

				UPlayerStateSlotWidget* playerStateSlot = playerController->GetPlayerStateSlotWidget();

				playerStateSlot->SetImageMaterial(supplyItemData->ItemType, supplyItemData->BuffImage);

				playerController->GetGameWidget()->FloatingWidgetPlayerState(playerStateSlot);

				// ���� ��ȯ�� 
				playerController->AddSupplyItemCode(itemCode);

			});

		supplyStoreWidget->InitializeSupplyItem(supplyItemBuyEvent);
		
		

		// ��� ���� �����մϴ�.
		UUniformGridSlot* slot = Cast<UUniformGridSlot>(supplyStoreWidget->Slot);
		slot->SetColumn(col);
		slot->SetRow(row);

		col += 1;
		if (col >= MAX_COLUMN)
		{
			col = 0;
			++row;
		}
	}
	

}


