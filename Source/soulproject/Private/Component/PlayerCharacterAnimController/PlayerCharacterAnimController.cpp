#include "Component/PlayerCharacterAnimController/PlayerCharacterAnimController.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"
#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerCharacterAnimController::UPlayerCharacterAnimController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCharacterAnimController::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AGameCharacter>(GetOwner());
}

void UPlayerCharacterAnimController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 속력을 얻습니다.
	FVector characterVelocity = OwnerCharacter->GetVelocity();
	characterVelocity.Z = 0.0f;
	float xySpeed = characterVelocity.Length();

	// 속력을 갱신합니다.
	ControlledAnimInstance->SetCurrentSpeed(xySpeed);

	// 땅에 닿음 상태를 갱신합니다.
	//bool isInAir = OwnerCharacter->GetMovementComponent()->IsFalling();
	bool isGrounded = OwnerCharacter->GetMovementComponent()->IsMovingOnGround();
	ControlledAnimInstance->SetGroundedState(isGrounded);

	// 방어 상태를 갱신합니다.
	bool isBlocking = OwnerCharacter->GetAttackComponent()->GetBlockState();
	ControlledAnimInstance->SetBlockState(isBlocking);

}

void UPlayerCharacterAnimController::SetAnimInstance(UPlayerCharacterAnimInstance* controlledAnimInstance)
{
	ControlledAnimInstance = controlledAnimInstance;
	ControlledAnimInstance->SetAnimController(this);
}

void UPlayerCharacterAnimController::OnAttackEnded()
{
	OwnerCharacter->GetAttackComponent()->ClearCurrentAttack();
}

void UPlayerCharacterAnimController::OnNextAttackCheckStarted()
{
	onNextAttackInputCheckStarted.ExecuteIfBound();
}

void UPlayerCharacterAnimController::OnNextAttackCheckFinished()
{
	onNextAttackInputCheckFinished.ExecuteIfBound();
}

void UPlayerCharacterAnimController::EnableAttackArea()
{
	onAttackAreaEnabled.ExecuteIfBound();
}

void UPlayerCharacterAnimController::DisableAttackArea()
{
	onAttackAreaDisabled.ExecuteIfBound();
}

void UPlayerCharacterAnimController::AllowMovementInput(bool allowMovementInput)
{
	onAllowMovementInput.ExecuteIfBound(allowMovementInput);
}

void UPlayerCharacterAnimController::OnHitFinished()
{
	OwnerCharacter->OnHitFinished();
	OwnerCharacter->GetAttackComponent()->CancelAttackState();
}

void UPlayerCharacterAnimController::OnRollFinished()
{
	onRollAnimFinished.ExecuteIfBound();
}

void UPlayerCharacterAnimController::OnRollStart()
{
	OwnerCharacter->GetPlayerCharacterMovementComponent()->StartRollingMovmement();
}




