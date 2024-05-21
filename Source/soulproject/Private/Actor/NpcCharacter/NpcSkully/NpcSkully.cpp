#include "Actor/NpcCharacter/NpcSkully/NpcSkully.h"
#include "Enum/Npc/NpcType.h"
#include "Object/InteractionParam/ComsumeNpcInteractParam/ComsumeNpcInteractParam.h"
#include "AnimInstance/Npc/NpcAnimInstance.h"

ANpcSkully::ANpcSkully()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SKULLY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Primitive_Characters_Pack/Mesh/Primitive_05/Mesh_UE5/Full/SKM_Primitive_05_01.SKM_Primitive_05_01'"));

	if (SK_SKULLY.Succeeded()) GetMesh()->SetSkeletalMesh(SK_SKULLY.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBP_NPC(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_Skully.AnimBP_Skully_C'"));

	if (ANIMBP_NPC.Succeeded()) GetMesh()->SetAnimClass(ANIMBP_NPC.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGETBP_ITEM(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/SkullyStoreWidget/WidgetBP_SkullyItem.WidgetBP_SkullyItem_C'"));

	if (WIDGETBP_ITEM.Succeeded()) BP_SkullyItemWidget = WIDGETBP_ITEM.Class;

	NpcCode = TEXT("000002");
	NpcType = ENpcType::SupplyBase;


}

bool ANpcSkully::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished);

	if (!result) return false;

	// 상호작용 애니메이션 재생
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}

UInteractionParamBase* ANpcSkully::GetInteractionParam()
{
	UComsumeNpcInteractParam* interactionParam = NewObject<UComsumeNpcInteractParam>(this);

	FString contextString;
	interactionParam->BP_SkullyItemWidgetClass = BP_SkullyItemWidget;

	return interactionParam;



	
}
