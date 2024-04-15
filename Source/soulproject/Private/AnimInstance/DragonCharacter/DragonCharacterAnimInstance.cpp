#include "AnimInstance/DragonCharacter/DragonCharacterAnimInstance.h"
#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"

void UDragonCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ADragonCharacter* dragonCharacter = Cast<ADragonCharacter>(GetOwningActor());

	// 유효성 검사
	if (!IsValid(dragonCharacter)) return;

	// 속도 갱신
	FVector velocity = dragonCharacter->GetVelocity();
	velocity.Z = 0.0f;
	XYSpeed = velocity.Length();
}

void UDragonCharacterAnimInstance::StartFly()
{
	IsFly = true;
	FlyDirection = FIntVector(0, 0, 1);
}

void UDragonCharacterAnimInstance::StartFalling()
{
	IsFly = true;
	FlyDirection = FIntVector(0, 0, -1);
}

void UDragonCharacterAnimInstance::FinishFlying()
{
	IsFly = false;
	FlyDirection = FIntVector(0, 0, 0);

}



void UDragonCharacterAnimInstance::AnimNotify_TurnLeft()
{
	OnTurn.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_TurnRight()
{
	OnTurn.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_DashFinished()
{
	OnDashFinished.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_OnBreathFireStarted()
{
	OnBreathFireStarted.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_OnBreathFireFinished()
{
	OnBreathFireFinished.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_OnClawAttackStarted()
{
	OnClawAttackStarted.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_OnClawAttackFinished()
{
	OnClawAttackFinished.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_OnRushAttackStarted()
{
	OnRushAttackStarted.Broadcast();
}

void UDragonCharacterAnimInstance::AnimNotify_OnRushAttackFinished()
{
	OnRushAttackFinished.Broadcast();
}
