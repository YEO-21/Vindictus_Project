#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerCharacterMovementComponent::UPlayerCharacterMovementComponent()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_ROLL(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/GirlKnight1/Animations/Roll/AnimMontage_Roll.AnimMontage_Roll'"));
	if (ANIMMONTAGE_ROLL.Succeeded())
	{
		RollAnimMontage = ANIMMONTAGE_ROLL.Object;
	}

	PrimaryComponentTick.bCanEverTick = true;

	AllowMovementInput = true;

	RollInputTime = -10;
	PrevRollInputDirection = FIntVector2(0, 0);
}

void UPlayerCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	GameCharacter = Cast<AGameCharacter>(GetOwner());
}

void UPlayerCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsRollingMovement)
	{
		GameCharacter->AddMovementInput(
			GameCharacter->GetActorForwardVector(), 1.0f);
	}

}

void UPlayerCharacterMovementComponent::HorizontalMove(float axis)
{
	axis = AllowMovementInput ? axis : 0.0f;

	// ��Ʈ�ѷ� ȸ���� Yaw ȸ������ ����ϴ�.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	FRotator yawRotation = FRotator(0.0f, gameCharacter->GetControlRotation().Yaw, 0.0f);

	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	//rightVector = Cast<AActor>(gameCharacter->GetController())->GetActorRightVector();
	gameCharacter->AddMovementInput(rightVector, axis);


}

void UPlayerCharacterMovementComponent::VerticalMove(float axis)
{
	axis = AllowMovementInput ? axis : 0.0f;

	// ��Ʈ�ѷ� ȸ���� Yaw ȸ������ ����ϴ�.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	FRotator yawRotation = FRotator(0.0f, gameCharacter->GetControlRotation().Yaw, 0.0f);

	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	//FVector controllerForward = Cast<AActor>(gameCharacter->GetController())->GetActorForwardVector();
	//controllerForward.Z = 0.0f;
	//forwardVector = controllerForward.GetUnsafeNormal();

	gameCharacter->AddMovementInput(forwardVector, axis);
}

void UPlayerCharacterMovementComponent::OnJump()
{
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	gameCharacter->Jump();
}

void UPlayerCharacterMovementComponent::OnHit()
{
	AllowMovementInput = false;
}

void UPlayerCharacterMovementComponent::OnRollInput(FIntVector2 inputDirection)
{
	// ���� Ŭ������ �νĵǵ��� �� �ð� ��
	const float DOUBLE_INPUT_TIMETERM = 0.2f;

	// �Էµ� ���� �ð��� ����ϴ�.
	float inputTime = GetWorld()->GetTimeSeconds();

	// ������ �Է��� ����� ������ ���
	if (inputDirection == PrevRollInputDirection &&

		// ���� Ŭ������ �Էµ� �ð� �ȿ� �Է��� ���
		inputTime < RollInputTime + DOUBLE_INPUT_TIMETERM)
	{
		// �����⸦ �����մϴ�.
		FVector rollingDirection = FVector(PrevRollInputDirection.Y, PrevRollInputDirection.X, 0.0f);
		RollingMovement(rollingDirection, inputDirection);

		// ���� �Է� ����� ���� ���� �ʱ�ȭ
		RollInputTime = -DOUBLE_INPUT_TIMETERM;
		PrevRollInputDirection = FIntVector2(0, 0);
	}
	else
	{
		// �Է� �ð��� ����մϴ�.
		RollInputTime = inputTime;

		// �Է� ������ ����մϴ�.
		PrevRollInputDirection = inputDirection;
	}

}

void UPlayerCharacterMovementComponent::OnRollFinished()
{
	IsRollingMovement = false;

	// �̵� �Է� ���
	AllowMovementInput = true;
}

void UPlayerCharacterMovementComponent::OnRunStarted()
{
	IsRun = true;
	GameCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void UPlayerCharacterMovementComponent::OnRunFinished()
{
	IsRun = false;
	GameCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void UPlayerCharacterMovementComponent::SetAllowMovementInput(bool allowMovementInput)
{
	AllowMovementInput = allowMovementInput;
}

void UPlayerCharacterMovementComponent::AddImpulse(FVector direction, float power)
{
	GameCharacter->LaunchCharacter(direction * power * 0.01f, true, false);
}

void UPlayerCharacterMovementComponent::StartRollingMovmement()
{

}

void UPlayerCharacterMovementComponent::RollingMovement(FVector rollDirection, FIntVector2 inputDirection)
{
	// �����߿��� ������� �ʵ��� �մϴ�.
	if (GameCharacter->GetAttackComponent()->GetAttackState()) return;

	// ���ظ� �Դ� ���̶�� ������� �ʵ��� �մϴ�.
	if (GameCharacter->GetHitState()) return;

	// ���߿����� ������� �ʵ��� �մϴ�.
	if (!GameCharacter->GetCharacterMovement()->IsMovingOnGround()) return;
	//if (GameCharacter->GetCharacterMovement()->IsFalling()) return;

	// ����߿��� �����Ⱑ ������� �ʵ��� �մϴ�.
	if (GameCharacter->GetAttackComponent()->GetBlockState()) return;

	// ������ �̵����� ��� ������� �ʵ��� �մϴ�.
	if (IsRollingMovement) return;

	// ������ �̵� ���·� �����մϴ�.
	IsRollingMovement = true;

	// �̵� �Է� ���
	AllowMovementInput = false;

	// ���� ���⿡ ���� Yaw ȸ�� ��
	float worldYawAngle = FMath::RadiansToDegrees(FMath::Atan2(rollDirection.Y, rollDirection.X));

	// ���� ĳ������ Yaw ȸ�� ��
	float characterYawAngle = GameCharacter->GetControlRotation().Yaw;

	// ������ �������� ȸ����ŵ�ϴ�.
	GameCharacter->SetActorRotation(FRotator(0.0f, worldYawAngle + characterYawAngle, 0.0f));

	// �ִϸ��̼� ��Ÿ�� ���
	GameCharacter->PlayAnimMontage(RollAnimMontage);
}


