#include "Actor/NpcCharacter/NpcSkully/NpcSkully.h"
#include "Enum/Npc/NpcType.h"
#include "AnimInstance/Npc/NpcAnimInstance.h"

ANpcSkully::ANpcSkully()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SKULLY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Primitive_Characters_Pack/Mesh/Primitive_05/Mesh_UE5/Full/SKM_Primitive_05_01.SKM_Primitive_05_01'"));

	if (SK_SKULLY.Succeeded()) GetMesh()->SetSkeletalMesh(SK_SKULLY.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBP_NPC(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_Skully.AnimBP_Skully_C'"));

	if (ANIMBP_NPC.Succeeded()) GetMesh()->SetAnimClass(ANIMBP_NPC.Class);

	NpcCode = TEXT("000002");
	NpcType = ENpcType::SupplyBase;


}

bool ANpcSkully::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished,
	class UInteractionParamBase* interactionParam)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished, interactionParam);

	if (!result) return false;

	// 상호작용 애니메이션 재생
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}
