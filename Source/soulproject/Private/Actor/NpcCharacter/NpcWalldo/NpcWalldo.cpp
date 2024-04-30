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

	// Npc 코드 설정
	NpcCode = TEXT("000001");
	// Npc 타입 설정
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

	// 거래가 가능한지를 확인하기 위해 대리자에 바인딩을 합니다.
	buyWeaponEvent.AddUObject(InteractableAreaComponent,
		&UInteractableAreaComponent::SetTradable);

	// 거래가 가능한 아이템의 코드를 얻어오기 위해 대리자에 바인딩을 합니다.
	getItemsignature.BindUObject(this, &ThisClass::GetWeaponCode);

	UWeaponNpcInteractParam* interactionParam = Cast<UWeaponNpcInteractParam>(GetInteractionParam());

	// 무기 상점 위젯을 얻습니다.
	UWeaponStoreWidget* weaponstoreWidget = CreateWidget<UWeaponStoreWidget>(
		GetWorld()->GetFirstPlayerController(),
		interactionParam->BP_WeaponStoreWidgetClass);

	// 대리자를 초기화합니다.
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

	// 대화 애니메이션 재생
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}
