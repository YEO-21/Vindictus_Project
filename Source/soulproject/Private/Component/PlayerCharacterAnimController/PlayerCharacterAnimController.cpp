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

	// �ӷ��� ����ϴ�.
	FVector characterVelocity = OwnerCharacter->GetVelocity();
	characterVelocity.Z = 0.0f;
	float xySpeed = characterVelocity.Length();

	// �ӷ��� �����մϴ�.
	ControlledAnimInstance->SetCurrentSpeed(xySpeed);

	// ���� ���� ���¸� �����մϴ�.
	//bool isInAir = OwnerCharacter->GetMovementComponent()->IsFalling();
	bool isGrounded = OwnerCharacter->GetMovementComponent()->IsMovingOnGround();
	ControlledAnimInstance->SetGroundedState(isGrounded);

	// ��� ���¸� �����մϴ�.
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




