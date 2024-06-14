#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Widget/StoreItemWidget/StoreItemWidget.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Image.h"

#include "Structure/PlayerWeaponData/PlayerWeaponData.h"

#include "../soulproject.h"

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


	
}

void UWeaponStoreWidget::InitializeWeaponStoreWidget(TArray<FName> itemCodes)
{
	int32 Collumn = 0;
	int32 Row = 0;

	// Get GameCharacter
	AGameCharacter* gameCharacter = 
		Cast<AGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	

	for (FName itemCode : itemCodes)
	{
		// 각 무기 코드로 초기화 시킵니다.
		gameCharacter->GetEquipWeaponComponent()->InitializeEquippedWeapon(itemCode);

		// 각 무기 위젯을 생성합니다.
		UStoreItemWidget* createdStoreItemWidget = 
			CreateWidget<UStoreItemWidget>(this, WidgetBP_StoreItemClass);

		TArray<UStoreItemWidget*> weaponWidgets;

		// 무기 UI 이미지를 얻습니다.
		UTexture2D* weaponImage = gameCharacter->GetEquipWeaponComponent()->PlayerWeaponData->WeaponImage;

		// 무기 UI 이미지를 설정합니다.
		createdStoreItemWidget->Image_Weapon->SetBrushFromTexture(weaponImage);

		// 위젯을 그리드에 추가하고 슬롯을 설정합니다.
		ItemGridPanel->AddChild(createdStoreItemWidget);
		UUniformGridSlot* slot = Cast<UUniformGridSlot>(createdStoreItemWidget->Slot);

		slot->SetColumn(Collumn);
		slot->SetRow(Row);
		
		Row += 2;

		UE_LOG(LogTemp, Warning, TEXT("itemCode = %s"), *itemCode.ToString());

		createdStoreItemWidget->WeaponCode = itemCode;
		

		// 버튼 클릭 이벤트 바인딩
		WeaponBuyButtonClickSignature onBuyButtonClicked;
		onBuyButtonClicked.AddLambda(
			[gameCharacter](FName buyItemCode) {

				// 무기 장착
				gameCharacter->EquippedWeaponCode = buyItemCode;
				gameCharacter->GetEquipWeaponComponent()->EquipWeapon();
			});

		// 이벤트 전달 및 초기화
		createdStoreItemWidget->InitializeStoreWidget(onBuyButtonClicked);
		
	}

	
}

void UWeaponStoreWidget::InitializeItemNameWidget(GetItemNameSignature itemName)
{
	GetItemName = itemName;
}

void UWeaponStoreWidget::InitializePassItemNameWidget(PassWeaponWidgetSignature passWeaponWidget)
{
	PassWeaponWidget = passWeaponWidget;
}

void UWeaponStoreWidget::OnBuyButtonClicked()
{
	PassWeaponWidget.Broadcast();
}







