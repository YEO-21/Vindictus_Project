#include "Actor/NpcCharacter/NpcSkully/NpcSkully.h"
#include "Enum/Npc/NpcType.h"
#include "Object/InteractionParam/SupplyNpcInteractParam/SupplyNpcInteractParam.h"

#include "Widget/SupplyItemGridWidget/SupplyItemGridWidget.h"

#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"
#include "AnimInstance/Npc/NpcAnimInstance.h"

ANpcSkully::ANpcSkully()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SKULLY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Primitive_Characters_Pack/Mesh/Primitive_05/Mesh_UE5/Full/SKM_Primitive_05_01.SKM_Primitive_05_01'"));

	if (SK_SKULLY.Succeeded()) GetMesh()->SetSkeletalMesh(SK_SKULLY.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBP_NPC(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_Skully.AnimBP_Skully_C'"));

	if (ANIMBP_NPC.Succeeded()) GetMesh()->SetAnimClass(ANIMBP_NPC.Class);

	static ConstructorHelpers::FClassFinder<USupplyItemGridWidget> WIDGET_SUPPLY(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/SkullyStoreWidget/WidgetBP_SkullyStore.WidgetBP_SkullyStore_C'"));

	if (WIDGET_SUPPLY.Succeeded()) BP_SupplyItemStoreWidgetClass = WIDGET_SUPPLY.Class;

	NpcCode = TEXT("000002");
	NpcType = ENpcType::SupplyBase;


}

bool ANpcSkully::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished);

	if (!result) return false;


	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}

UInteractionParamBase* ANpcSkully::GetInteractionParam()
{
	Super::GetInteractionParam();

	USupplyNpcInteractParam* interactionParam = NewObject<USupplyNpcInteractParam>(this);
	interactionParam->BP_SupplyStoreWidgetClass = BP_SupplyItemStoreWidgetClass;
	UE_LOG(LogTemp, Warning, TEXT("%d"), IsValid(BP_SupplyItemStoreWidgetClass));

	return interactionParam;
}
