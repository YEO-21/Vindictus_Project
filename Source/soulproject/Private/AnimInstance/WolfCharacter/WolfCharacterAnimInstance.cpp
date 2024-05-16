#include "AnimInstance/WolfCharacter/WolfCharacterAnimInstance.h"

#include "Actor/EnemyCharacter/Wolf/WolfCharacter.h"
#include "Actor/EnemyController/Wolf/WolfController.h"


void UWolfCharacterAnimInstance::SetCurrentSpeed(float newSpeed)
{
	CurrentSpeed = newSpeed;
}

void UWolfCharacterAnimInstance::SetWolfStateNumber(float newNumber)
{
	WolfStateNumber = newNumber;
}

void UWolfCharacterAnimInstance::AnimNotify_OnAttackFinished()
{
	AWolfController* wolfController = Cast<AWolfController>(
		Cast<AWolfCharacter>(GetOwningActor())->GetController());

	if (!IsValid(wolfController)) return;

	wolfController->OnAttackFinished();
}
