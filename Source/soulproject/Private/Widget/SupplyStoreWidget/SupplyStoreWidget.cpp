#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

USupplyStoreWidget::USupplyStoreWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SUPPLYDATA(
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_SupplyItemData.DT_SupplyItemData'"));

	if (DT_SUPPLYDATA.Succeeded()) DT_SupplyItemData = DT_SUPPLYDATA.Object;

	
	
}

void USupplyStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_SupplyItem->OnClicked.AddUniqueDynamic(this, &ThisClass::OnBuyButtonClicked);

}


void USupplyStoreWidget::SetSupplyItemCode(FName itemCode)
{
	SupplyItemCode = itemCode;
}

void USupplyStoreWidget::SetImageMaterial(UMaterialInterface* material)
{
	Image_SupplyItem->SetBrushFromMaterial(material);
}

void USupplyStoreWidget::SetText(FText text)
{
	TextBlock_SupplyItem->SetText(text);
}

void USupplyStoreWidget::InitializeSupplyStoreWidget()
{
	




}

void USupplyStoreWidget::InitializeItemCode(FName itemCode)
{
	SupplyItemCode = itemCode;

	if (SupplyItemCode.IsNone())
	{
		PlayerSupplyData = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("SupplyItemCode is not valid!"));
		return;
	}

	FString contextstring;
	PlayerSupplyData = DT_SupplyItemData->FindRow<FSupplyItemData>(SupplyItemCode, contextstring);

}

void USupplyStoreWidget::InitializeSupplyItem(SupplyItemBuyButtonClickSignature supplyEvent)
{
	SupplyItemBuyEvent = supplyEvent;
}


void USupplyStoreWidget::OnBuyButtonClicked()
{
	SupplyItemBuyEvent.Broadcast();

}
