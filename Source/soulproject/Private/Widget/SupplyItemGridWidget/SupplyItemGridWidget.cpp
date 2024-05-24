#include "Widget/SupplyItemGridWidget/SupplyItemGridWidget.h"
#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"

#include "Structure/SupplyItemData/SupplyItemData.h"

#include "Component/PlayerBuffControlComponent/PlayerBuffControlComponent.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Actor/GameCharacter/GameCharacter.h"

USupplyItemGridWidget::USupplyItemGridWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<USupplyStoreWidget> WIDGETBP_SUPPLY(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/SkullyStoreWidget/WidgetBP_SupplyItem.WidgetBP_SupplyItem_C'"));

	if (WIDGETBP_SUPPLY.Succeeded()) WidgetBP_SkullyStore = WIDGETBP_SUPPLY.Class;

	

}

void USupplyItemGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 아이템 코드를 배열에 추가합니다.
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

	
	for (FName itemCode : itemCodes)
	{
		// 아이템 위젯을 생성합니다.
		USupplyStoreWidget* supplyStoreWidget = CreateWidget<USupplyStoreWidget>(this, WidgetBP_SkullyStore);

		// 아이템 코드 정보를 초기화합니다.
		supplyStoreWidget->InitializeItemCode(itemCode);

		FSupplyItemData* supplyItemData = supplyStoreWidget->PlayerSupplyData;

		// 아이템 위젯의 이미지를 설정합니다.
		supplyStoreWidget->SetImageMaterial(supplyItemData->BuffImage);

		// 아이템 위젯의 텍스트를 설정합니다.
		supplyStoreWidget->SetText(supplyItemData->ItemEffect);

		// 그리드 패널에 위젯을 추가합니다.
		ItemGridPanel->AddChild(supplyStoreWidget);




		SupplyItemBuyButtonClickSignature supplyItemBuyEvent;
		supplyItemBuyEvent.AddLambda([supplyItemData, gameCharacter]()
			{
				gameCharacter->GetBuffControlComponent()->SupplyItemLists.Add(supplyItemData->ItemType);


			});

		supplyStoreWidget->InitializeSupplyItem(supplyItemBuyEvent);

		

		// 행과 열을 설정합니다.
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


