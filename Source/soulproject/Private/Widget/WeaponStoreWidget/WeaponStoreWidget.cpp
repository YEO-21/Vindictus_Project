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
		// �� ���� �ڵ�� �ʱ�ȭ ��ŵ�ϴ�.
		gameCharacter->GetEquipWeaponComponent()->InitializeEquippedWeapon(itemCode);

		// �� ���� ������ �����մϴ�.
		UStoreItemWidget* createdStoreItemWidget = 
			CreateWidget<UStoreItemWidget>(this, WidgetBP_StoreItemClass);

		TArray<UStoreItemWidget*> weaponWidgets;

		// ���� UI �̹����� ����ϴ�.
		UTexture2D* weaponImage = gameCharacter->GetEquipWeaponComponent()->PlayerWeaponData->WeaponImage;

		// ���� UI �̹����� �����մϴ�.
		createdStoreItemWidget->Image_Weapon->SetBrushFromTexture(weaponImage);

		// ������ �׸��忡 �߰��ϰ� ������ �����մϴ�.
		ItemGridPanel->AddChild(createdStoreItemWidget);
		UUniformGridSlot* slot = Cast<UUniformGridSlot>(createdStoreItemWidget->Slot);

		slot->SetColumn(Collumn);
		slot->SetRow(Row);
		
		Row += 2;

		UE_LOG(LogTemp, Warning, TEXT("itemCode = %s"), *itemCode.ToString());

		createdStoreItemWidget->WeaponCode = itemCode;
		

		// ��ư Ŭ�� �̺�Ʈ ���ε�
		WeaponBuyButtonClickSignature onBuyButtonClicked;
		onBuyButtonClicked.AddLambda(
			[gameCharacter](FName buyItemCode) {

				// ���� ����
				gameCharacter->EquippedWeaponCode = buyItemCode;
				gameCharacter->GetEquipWeaponComponent()->EquipWeapon();
			});

		// �̺�Ʈ ���� �� �ʱ�ȭ
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







