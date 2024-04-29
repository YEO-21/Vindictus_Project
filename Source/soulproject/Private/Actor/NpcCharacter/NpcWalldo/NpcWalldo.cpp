#include "Actor/NpcCharacter/NpcWalldo/NpcWalldo.h"
#include "AnimInstance/Npc/NpcAnimInstance.h"
#include "Object/InteractionParam/WeaponNpcInteractParam/WeaponNpcInteractParam.h"
#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Structure/NpcData/NpcData.h"

#include "Enum/Npc/NpcType.h"

ANpcWalldo::ANpcWalldo()
{
	static ConstructorHelpers::FClassFinder<UWeaponStoreWidget> BP_WEAPONSTORECLASS(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/WeaponStoreWidget/WidgetBP_WeaponStore.WidgetBP_WeaponStore_C'"));
	if (BP_WEAPONSTORECLASS.Succeeded()) BP_WeaponStoreWidgetClass = BP_WEAPONSTORECLASS.Class;

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

bool ANpcWalldo::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished);

	if (!result) return false;

	// 대화 애니메이션 재생
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}
