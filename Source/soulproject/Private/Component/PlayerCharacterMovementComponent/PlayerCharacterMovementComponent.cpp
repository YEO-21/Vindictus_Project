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

	// 컨트롤러 회전중 Yaw 회전만을 얻습니다.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	FRotator yawRotation = FRotator(0.0f, gameCharacter->GetControlRotation().Yaw, 0.0f);

	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	//rightVector = Cast<AActor>(gameCharacter->GetController())->GetActorRightVector();
	gameCharacter->AddMovementInput(rightVector, axis);


}

void UPlayerCharacterMovementComponent::VerticalMove(float axis)
{
	axis = AllowMovementInput ? axis : 0.0f;

	// 컨트롤러 회전중 Yaw 회전만을 얻습니다.
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
	// 더블 클릭으로 인식되도록 할 시간 텀
	const float DOUBLE_INPUT_TIMETERM = 0.2f;

	// 입력된 현재 시간을 얻습니다.
	float inputTime = GetWorld()->GetTimeSeconds();

	// 이전에 입력한 방향과 동일한 경우
	if (inputDirection == PrevRollInputDirection &&

		// 더블 클릭으로 입력될 시간 안에 입력한 경우
		inputTime < RollInputTime + DOUBLE_INPUT_TIMETERM)
	{
		// 구르기를 실행합니다.
		FVector rollingDirection = FVector(PrevRollInputDirection.Y, PrevRollInputDirection.X, 0.0f);
		RollingMovement(rollingDirection, inputDirection);

		// 이전 입력 기록을 위한 변수 초기화
		RollInputTime = -DOUBLE_INPUT_TIMETERM;
		PrevRollInputDirection = FIntVector2(0, 0);
	}
	else
	{
		// 입력 시간을 기록합니다.
		RollInputTime = inputTime;

		// 입력 방향을 기록합니다.
		PrevRollInputDirection = inputDirection;
	}

}

void UPlayerCharacterMovementComponent::OnRollFinished()
{
	IsRollingMovement = false;

	// 이동 입력 허용
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
	// 공격중에는 실행되지 않도록 합니다.
	if (GameCharacter->GetAttackComponent()->GetAttackState()) return;

	// 피해를 입는 중이라면 실행되지 않도록 합니다.
	if (GameCharacter->GetHitState()) return;

	// 공중에서는 실행되지 않도록 합니다.
	if (!GameCharacter->GetCharacterMovement()->IsMovingOnGround()) return;
	//if (GameCharacter->GetCharacterMovement()->IsFalling()) return;

	// 방어중에는 구르기가 실행되지 않도록 합니다.
	if (GameCharacter->GetAttackComponent()->GetBlockState()) return;

	// 구르기 이동중인 경우 실행되지 않도록 합니다.
	if (IsRollingMovement) return;

	// 구르기 이동 상태로 설정합니다.
	IsRollingMovement = true;

	// 이동 입력 블록
	AllowMovementInput = false;

	// 월드 방향에 대한 Yaw 회전 각
	float worldYawAngle = FMath::RadiansToDegrees(FMath::Atan2(rollDirection.Y, rollDirection.X));

	// 현재 캐릭터의 Yaw 회전 각
	float characterYawAngle = GameCharacter->GetControlRotation().Yaw;

	// 구르는 방향으로 회전시킵니다.
	GameCharacter->SetActorRotation(FRotator(0.0f, worldYawAngle + characterYawAngle, 0.0f));

	// 애니메이션 몽타주 재생
	GameCharacter->PlayAnimMontage(RollAnimMontage);
}


