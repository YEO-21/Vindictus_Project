#include "Actor/NpcCharacter/NpcWalldo/NpcWalldo.h"
#include "AnimInstance/Npc/NpcAnimInstance.h"

ANpcWalldo::ANpcWalldo()
{
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

	NpcCode = TEXT("000001");

}

bool ANpcWalldo::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished);

	if (!result) return false;

	// 대화 애니메이션 재생
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}
