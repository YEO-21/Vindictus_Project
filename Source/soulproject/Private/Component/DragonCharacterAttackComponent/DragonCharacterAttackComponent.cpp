#include "Component/DragonCharacterAttackComponent/DragonCharacterAttackComponent.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Structure/EnemyData/EnemyData.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UDragonCharacterAttackComponent::UDragonCharacterAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DRAGON_PARRIED_ANIMMONTAGE(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/DesertDragon/Animations/AnimMontage_Parried.AnimMontage_Parried'"));

	ParriedAnimMontage = DRAGON_PARRIED_ANIMMONTAGE.Object;
	// ...
}


// Called when the game starts
void UDragonCharacterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDragonCharacterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 드래곤의 공격을 감지합니다.
	if (bIsAttackCheckEnabled) CheckAttackArea();

	// ...
}

void UDragonCharacterAttackComponent::StartBreathFire()
{
	IsBreathFire = true;
}

void UDragonCharacterAttackComponent::OnBreathFireFinished()
{
	IsBreathFire = false;
}

void UDragonCharacterAttackComponent::StartClawAttack()
{
	IsClawAttack = true;
}

void UDragonCharacterAttackComponent::FinishClawAttack()
{
	IsClawAttack = false;
}

void UDragonCharacterAttackComponent::StartRushAttack()
{
	IsRushAttack = true;
}

void UDragonCharacterAttackComponent::FinishRushAttack()
{
	IsRushAttack = false;
}

void UDragonCharacterAttackComponent::EnableAttackArea()
{
	bIsAttackCheckEnabled = true;
}

void UDragonCharacterAttackComponent::DisableAttackArea()
{
	bIsAttackCheckEnabled = false;
}




void UDragonCharacterAttackComponent::CheckAttackArea()
{
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());
	TArray<FHitResult> hitResults;

	// Get DragonCharacter
	ADragonCharacter* dragon = Cast<ADragonCharacter>(GetOwner());

	// 왼쪽 다리 공격 소켓 위치
	FVector leftlegStartLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_LEFTLEG_SOCKET_START).GetLocation();
	FVector leftlegEndLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_LEFTLEG_SOCKET_END).GetLocation();

	// 오른쪽 다리 공격 소켓 위치
	FVector rightlegStartLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_RIGHTLEG_SOCKET_START).GetLocation();
	FVector rightlegEndLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_RIGHTLEG_SOCKET_END).GetLocation();

	// 왼쪽 공격 체크
	UKismetSystemLibrary::SphereTraceMultiByProfile(
		this,
		leftlegStartLocation,
		leftlegEndLocation,
		150.0f,
		TEXT("AttackArea"),
		false,
		actorsToIgnore,
		EDrawDebugTrace::ForDuration,
		hitResults,
		true);

	// 오른쪽 공격 체크
	UKismetSystemLibrary::SphereTraceMultiByProfile(
		this,
		rightlegStartLocation,
		rightlegEndLocation,
		150.0f,
		TEXT("AttackArea"),
		false,
		actorsToIgnore,
		EDrawDebugTrace::ForDuration,
		hitResults,
		true);

	bool applyHalfDamage = false;

	for (FHitResult hitResult : hitResults)
	{
		// 감지된 객체 중, GameCharacter 형태의 객체를 얻습니다.
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(hitResult.GetActor());

		UE_LOG(LogTemp, Warning, TEXT("Check is Succeed!"));


		if (!IsValid(gameCharacter)) return;

		float PlayerCurrentHp = gameCharacter->GetCurrentHp();

		float damage = dragon->GetEnemyData()->Atk;


		// 플레이어 체력이 0보다 작으면 사망 처리
		if (PlayerCurrentHp < 0.0f)
		{
			dragon->PlayerDead();
			return;
		}

		// 만약 GameCharacter 객체를 감지한 경우
		if (IsValid(gameCharacter))
		{
			// 방어되었음을 확인합니다.
			bool isBlocked = IsBlocked(gameCharacter, dragon);

			UE_LOG(LogTemp, Warning, TEXT("gameCharacter is damaged!"));

			// 방어 처리된 경우
			if (isBlocked)
			{
				// 정확한 시간에 방어했음을 확인합니다.
				float currentTime = GetWorld()->GetTimeSeconds();
				float blockStartedTime = gameCharacter->GetAttackComponent()->GetBlockStartTime();
				applyHalfDamage = currentTime - blockStartedTime > 0.5f;

				dragon->PlayAnimMontage(ParriedAnimMontage);

				// 공격 끝
				TempDamagedActors.Empty();

				// 공격 영역 비활성화
				DisableAttackArea();

				// 피해를 주지 않아도 되는 경우 공격 처리가 이루어지지 않도록 합니다.
				if (!applyHalfDamage) return;
			}

			if (!isBlocked || applyHalfDamage)
			{
				// 공격 중복 처리
				if (!TempDamagedActors.Contains(gameCharacter))
				{
					TempDamagedActors.Add(gameCharacter);

					// 플레이어 캐릭터에게 피해를 입힙니다.
					UGameplayStatics::ApplyDamage(
						gameCharacter,
						damage * (applyHalfDamage ? 0.5f : 1.0f),
						dragon->GetController(),
						dragon,
						UDamageType::StaticClass());
				}
			}
		}
	}


}

bool UDragonCharacterAttackComponent::IsBlocked(
	AGameCharacter* gameCharacter, AActor* ownerEnemy) const
{
	FVector gameCharacterForward = gameCharacter->GetActorForwardVector();
	FVector enemyCharacterForward = GetOwner()->GetActorForwardVector();
	enemyCharacterForward *= -1;
	gameCharacterForward.Z = enemyCharacterForward.Z = 0.0f;

	float angle = FMath::RadiansToDegrees(
		FMathf::ACos(FVector::DotProduct(gameCharacterForward, enemyCharacterForward)));

	// 방어중이며, 방어할 수 있는 각도인 경우
	if (gameCharacter->GetAttackComponent()->GetBlockState() && angle <= 30.0f)
	{
		return true;
	}

	return false;
}

