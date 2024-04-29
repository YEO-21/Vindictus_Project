#include "Actor/NpcCharacter/NpcWalldo/NpcWalldo.h"
#include "AnimInstance/Npc/NpcAnimInstance.h"
#include "Enum/Npc/NpcType.h"

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

	// Npc �ڵ� ����
	NpcCode = TEXT("000001");
	// Npc Ÿ�� ����
	NpcType = ENpcType::WeaponBase;

}

bool ANpcWalldo::OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished
	, class UInteractionParamBase* interactionParam)
{
	bool result = Super::OnInteractionStarted(onInteractionFinished, interactionParam);

	if (!result) return false;

	// ��ȭ �ִϸ��̼� ���
	Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance())->SetTalkState(true);

	return true;
}
