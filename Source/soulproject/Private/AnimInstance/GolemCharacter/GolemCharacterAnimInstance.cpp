#include "AnimInstance/GolemCharacter/GolemCharacterAnimInstance.h"

#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"
#include "Actor/EnemyController/Golem/GolemController.h"

void UGolemCharacterAnimInstance::AnimNotify_GolemAttackEnd()
{
	// �� ��Ʈ�ѷ��� ����ϴ�.
	AGolemCharacter* golem = Cast<AGolemCharacter>(GetOwningActor());
	AGolemController* golemController = Cast<AGolemController>(golem->GetController());

	golemController->FinishAttack();
}
