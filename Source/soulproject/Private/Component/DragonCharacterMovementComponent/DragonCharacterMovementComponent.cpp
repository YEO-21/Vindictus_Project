#include "Component/DragonCharacterMovementComponent/DragonCharacterMovementComponent.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"

UDragonCharacterMovementComponent::UDragonCharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDragonCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	DragonCharacter = Cast<ADragonCharacter>(GetOwner());
}

void UDragonCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsYawTurning)
	{
		TurningSmooth(DeltaTime);
	}

	if (IsDash)
	{
		CheckDashFinish();
	}

	if (IsFly)
	{
		FlyMovement(DeltaTime);
	}

}

void UDragonCharacterMovementComponent::TurningSmooth(float dt)
{
	// 현재 회전
	FRotator currentRotation = DragonCharacter->GetActorRotation();

	// 목표 회전
	FRotator targetRotation = FRotator(0.0f, TargetYawAngle, 0.0f);

	if (IsYawTernFinished())
	{
		TargetYawAngle = targetRotation.Yaw;
		DragonCharacter->SetActorRotation(targetRotation);

		IsYawTurning = false;
	}
	else
	{
		// 부드럽게 회전
		FRotator newRotation = FMath::RInterpTo(
			currentRotation,
			targetRotation,
			dt, 15.0f);

		DragonCharacter->SetActorRotation(newRotation);
	}
}

void UDragonCharacterMovementComponent::CheckDashFinish()
{
	float speed = DragonCharacter->GetVelocity().Size();

	if (speed < 0.1)
	{
		IsDash = false;
	}
}

void UDragonCharacterMovementComponent::FlyMovement(float dt)
{
	USkeletalMeshComponent* bodyMesh = DragonCharacter->GetMesh();
	
	FVector currentLocation = bodyMesh->GetRelativeLocation();
	FVector targetLocation = FVector::UpVector * FlyTargetHeight;

	FVector nextLocation;

	if (IsFalling)
	{
		nextLocation = currentLocation + 
			FVector::DownVector * 3000.0f * dt;

		if (nextLocation.Z < targetLocation.Z)
		{
			IsFalling = false;
			nextLocation.Z = targetLocation.Z;
		}
		bodyMesh->SetRelativeLocation(nextLocation);
		
	}
	else
	{
		bodyMesh->SetRelativeLocation(FMath::VInterpTo(
			bodyMesh->GetRelativeLocation(),
			targetLocation,
			dt, 1.5f));
	}

	if (FVector::Distance(currentLocation, targetLocation) < 1.0f)
	{
		bodyMesh->SetRelativeLocation(targetLocation);
		IsFly = false;
	}

	

	
}


void UDragonCharacterMovementComponent::SetTargetYawAngle(float targetYawAngle)
{
	TargetYawAngle = targetYawAngle;
}

void UDragonCharacterMovementComponent::StartTurn()
{
	IsYawTurning = true;
}

void UDragonCharacterMovementComponent::StartFlyUp(float targetHeight)
{
	if (!IsFly)
	{
		IsFly = true;
		FlyTargetHeight = targetHeight;

		USkeletalMeshComponent* bodyMesh = DragonCharacter->GetMesh();
		BodyMeshLocation = bodyMesh->GetRelativeLocation();
	}

}

void UDragonCharacterMovementComponent::StartFalling()
{
	if (!IsFly)
	{
		IsFly = true;
		IsFalling = true;
		FlyTargetHeight = BodyMeshLocation.Z;
	}
}

void UDragonCharacterMovementComponent::FinishFlying()
{
	IsFly = false;
	IsFalling = false;

}

void UDragonCharacterMovementComponent::StartDash(FVector direction, float power)
{
	IsDash = true;
	DragonCharacter->LaunchCharacter(direction, power);
	DragonCharacter->PlayMoveAnimMontage(ANIMMONTAGE_SECTION_DASHBACKWARD);

}

bool UDragonCharacterMovementComponent::IsYawTernFinished()
{
	// 현재 회전
	FRotator currentRotation = DragonCharacter->GetActorRotation();

	// 목표 회전
	FRotator targetRotation = FRotator(0.0f, TargetYawAngle, 0.0f);

	return currentRotation.Equals(targetRotation, 5.0f);
}

