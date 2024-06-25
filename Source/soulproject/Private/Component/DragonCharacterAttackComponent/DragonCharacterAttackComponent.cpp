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

	// �巡���� ������ �����մϴ�.
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

	// ���� �ٸ� ���� ���� ��ġ
	FVector leftlegStartLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_LEFTLEG_SOCKET_START).GetLocation();
	FVector leftlegEndLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_LEFTLEG_SOCKET_END).GetLocation();

	// ������ �ٸ� ���� ���� ��ġ
	FVector rightlegStartLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_RIGHTLEG_SOCKET_START).GetLocation();
	FVector rightlegEndLocation = dragon->GetMesh()->GetSocketTransform(DRAGON_ATTACK_RIGHTLEG_SOCKET_END).GetLocation();

	// ���� ���� üũ
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

	// ������ ���� üũ
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
		// ������ ��ü ��, GameCharacter ������ ��ü�� ����ϴ�.
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(hitResult.GetActor());

		UE_LOG(LogTemp, Warning, TEXT("Check is Succeed!"));


		if (!IsValid(gameCharacter)) return;

		float PlayerCurrentHp = gameCharacter->GetCurrentHp();

		float damage = dragon->GetEnemyData()->Atk;


		// �÷��̾� ü���� 0���� ������ ��� ó��
		if (PlayerCurrentHp < 0.0f)
		{
			dragon->PlayerDead();
			return;
		}

		// ���� GameCharacter ��ü�� ������ ���
		if (IsValid(gameCharacter))
		{
			// ���Ǿ����� Ȯ���մϴ�.
			bool isBlocked = IsBlocked(gameCharacter, dragon);

			UE_LOG(LogTemp, Warning, TEXT("gameCharacter is damaged!"));

			// ��� ó���� ���
			if (isBlocked)
			{
				// ��Ȯ�� �ð��� ��������� Ȯ���մϴ�.
				float currentTime = GetWorld()->GetTimeSeconds();
				float blockStartedTime = gameCharacter->GetAttackComponent()->GetBlockStartTime();
				applyHalfDamage = currentTime - blockStartedTime > 0.5f;

				dragon->PlayAnimMontage(ParriedAnimMontage);

				// ���� ��
				TempDamagedActors.Empty();

				// ���� ���� ��Ȱ��ȭ
				DisableAttackArea();

				// ���ظ� ���� �ʾƵ� �Ǵ� ��� ���� ó���� �̷������ �ʵ��� �մϴ�.
				if (!applyHalfDamage) return;
			}

			if (!isBlocked || applyHalfDamage)
			{
				// ���� �ߺ� ó��
				if (!TempDamagedActors.Contains(gameCharacter))
				{
					TempDamagedActors.Add(gameCharacter);

					// �÷��̾� ĳ���Ϳ��� ���ظ� �����ϴ�.
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

	// ������̸�, ����� �� �ִ� ������ ���
	if (gameCharacter->GetAttackComponent()->GetBlockState() && angle <= 30.0f)
	{
		return true;
	}

	return false;
}

