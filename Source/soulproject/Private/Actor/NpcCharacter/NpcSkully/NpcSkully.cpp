#include "Actor/NpcCharacter/NpcSkully/NpcSkully.h"

ANpcSkully::ANpcSkully()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SKULLY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Primitive_Characters_Pack/Mesh/Primitive_05/Mesh_UE5/Full/SKM_Primitive_05_01.SKM_Primitive_05_01'"));

	if (SK_SKULLY.Succeeded()) GetMesh()->SetSkeletalMesh(SK_SKULLY.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBP_NPC(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_Skully.AnimBP_Skully_C'"));

	if (ANIMBP_NPC.Succeeded()) GetMesh()->SetAnimClass(ANIMBP_NPC.Class);

	NpcCode = TEXT("000002");


}

bool ANpcSkully::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished);

	if (!result) return false;



	return true;
}
