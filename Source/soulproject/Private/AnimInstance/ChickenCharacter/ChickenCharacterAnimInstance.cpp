#include "AnimInstance/ChickenCharacter/ChickenCharacterAnimInstance.h"

void UChickenCharacterAnimInstance::SetIsDead(bool isDead)
{
	IsDead = isDead;
}

void UChickenCharacterAnimInstance::SetCurrentSpeed(float newSpeed)
{
	CurrentSpeed = newSpeed;
}
