#include "AnimInstance/KnightCharacter/KnightCharacterAnimInstance.h"
#include "Actor/EnemyCharacter/Knight/KnightCharacter.h"
#include "Actor/EnemyController/Knight/KnightController.h"

#include "Component/KnightAttackComponent/KnightAttackComponent.h"

void UKnightCharacterAnimInstance::SetCurrentSpeed(float newSpeed)
{
	CurrentSpeed = newSpeed;
}

void UKnightCharacterAnimInstance::AnimNotify_OnAttackFinished()
{
	AKnightCharacter* knightCharacter = Cast<AKnightCharacter>(GetOwningActor());
	AKnightController* knightController = Cast<AKnightController>(knightCharacter->GetController());

	// 공격 종료
	knightController->OnAttackFinished();
	knightCharacter->GetAttackComponent()->OnAttackFinished();
}

void UKnightCharacterAnimInstance::AnimNotify_EnableAttackArea()
{
	AKnightCharacter* knightCharacter = Cast<AKnightCharacter>(GetOwningActor());
	knightCharacter->GetAttackComponent()->EnableAttackArea();
}

void UKnightCharacterAnimInstance::AnimNotify_DisableAttackArea()
{
	AKnightCharacter* knightCharacter = Cast<AKnightCharacter>(GetOwningActor());
	knightCharacter->GetAttackComponent()->DisableAttackArea();
}

void UKnightCharacterAnimInstance::AnimNotify_ParriedMotionFinished()
{
	AnimNotify_OnAttackFinished();
}

void UKnightCharacterAnimInstance::AnimNotify_HitMotionFinished()
{
	AnimNotify_OnAttackFinished();
}
