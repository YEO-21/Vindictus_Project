#include "Actor/NpcCharacter/NpcWalldo/NpcWalldo.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "AnimInstance/Npc/NpcAnimInstance.h"
#include "Object/InteractionParam/WeaponNpcInteractParam/WeaponNpcInteractParam.h"
#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Widget/StoreItemWidget/StoreItemWidget.h"
#include "Structure/NpcData/NpcData.h"

#include "Component/InteractableAreaComponent/InteractableAreaComponent.h"

#include "Enum/Npc/NpcType.h"

ANpcWalldo::ANpcWalldo()
{
	static ConstructorHelpers::FClassFinder<UWeaponStoreWidget> BP_WEAPONSTORECLASS(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/WeaponStoreWidget/WidgetBP_WeaponStore.WidgetBP_WeaponStore_C'"));
	if (BP_WEAPONSTORECLASS.Succeeded()) BP_WeaponStoreWidgetClass = BP_WEAPONSTORECLASS.Class;

	static ConstructorHelpers::FClassFinder<UStoreItemWidget> BP_STOREITEMCLASS(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/WeaponStoreWidget/WidgetBP_StoreItem.WidgetBP_StoreItem_C'"));
	if (BP_STOREITEMCLASS.Succeeded()) ItemWidgetClass = BP_STOREITEMCLASS.Class;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_BODY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/NPC/Walldo/Brute.Brute'"));

	static ConstructorHelpers::FClassFinder<UNpcAnimInstance> ANIMBP_NPC(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_Walldo.AnimBP_Walldo_C'"));


	

	if (SM_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_BODY.Object);
	}
	if (ANIMBP_NPC.Succeeded())
	{
		GetMesh()->SetAnimClass(ANIMBP_NPC.Class);
	}

	// Npc �ڵ� ����
	NpcCode = TEXT("000001");
	// Npc Ÿ�� ����
	NpcType = ENpcType::WeaponBase;

}

UInteractionParamBase* ANpcWalldo::GetInteractionParam()
{
	UWeaponNpcInteractParam* interactionParam = NewObject<UWeaponNpcInteractParam>(this);
	interactionParam->BP_WeaponStoreWidgetClass = BP_WeaponStoreWidgetClass;

	return interactionParam;
}

FName ANpcWalldo::GetWeaponCode()
{
	// Get ItemWidget
	UStoreItemWidget* storeItemWidget =
		CreateWidget<UStoreItemWidget>(GetWorld()->GetFirstPlayerController(),
			ItemWidgetClass);

	UE_LOG(LogTemp, Warning, TEXT("storeItemWidget->WeaponCode is %s"), *storeItemWidget->WeaponCode.ToString());
	return storeItemWidget->WeaponCode;
}

void ANpcWalldo::BeginPlay()
{
	Super::BeginPlay();

	CheckTradable();
}

void ANpcWalldo::CheckTradable()
{
	//GetWeaponCode();

	GetItemNameSignature getItemsignature;
	WeaponBuyButtonClickSignature buyWeaponEvent;

	// �ŷ��� ���������� Ȯ���ϱ� ���� �븮�ڿ� ���ε��� �մϴ�.
	buyWeaponEvent.AddUObject(InteractableAreaComponent,
		&UInteractableAreaComponent::SetTradable);

	// �ŷ��� ������ �������� �ڵ带 ������ ���� �븮�ڿ� ���ε��� �մϴ�.
	getItemsignature.BindUObject(this, &ThisClass::GetWeaponCode);

	UWeaponNpcInteractParam* interactionParam = Cast<UWeaponNpcInteractParam>(GetInteractionParam());

	// ���� ���� ������ ����ϴ�.
	UWeaponStoreWidget* weaponstoreWidget = CreateWidget<UWeaponStoreWidget>(
		GetWorld()->GetFirstPlayerController(),
		interactionParam->BP_WeaponStoreWidgetClass);

	// �븮�ڸ� �ʱ�ȭ�մϴ�.
	//weaponstoreWidget->InitializeWeaponStoreWidget(buyWeaponEvent);
	TArray<FName> items;
	items.Add(TEXT("000001"));
	items.Add(TEXT("000002"));
	items.Add(TEXT("000003"));
	items.Add(TEXT("000004"));
	items.Add(TEXT("000005"));
	weaponstoreWidget->InitializeWeaponStoreWidget(items)
	//weaponstoreWidget->InitializeItemNameWidget(getItemsignature);
}



bool ANpcWalldo::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished);

	if (!result) return false;

	// ��ȭ �ִϸ��̼� ���
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}
