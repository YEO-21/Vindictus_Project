#include "Component/KnightAttackComponent/KnightAttackComponent.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"
#include "Actor/EnemyCharacter/Knight/KnightCharacter.h"
#include"Actor/EnemyController/EnemyController.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"
#include "Structure/EnemyData/EnemyData.h"


#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"



UKnightAttackComponent::UKnightAttackComponent()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MONTAGE_ATTACK(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/GKnight/Animation/AnimMontage_Attack.AnimMontage_Attack'"));
	if (MONTAGE_ATTACK.Succeeded())
	{
		AttackAnimMontage = MONTAGE_ATTACK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MONTAGE_PARRIED(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/GKnight/Animation/AnimMontage_Parried.AnimMontage_Parried'"));
	if (MONTAGE_PARRIED.Succeeded())
	{
		ParriedAnimMontage = MONTAGE_PARRIED.Object;
	}

	PrimaryComponentTick.bCanEverTick = true;
}

void UKnightAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UKnightAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���� ���� Ȯ��
	if (IsAttackAreaEnabled) CheckAttackArea();
}

bool UKnightAttackComponent::IsBlocked(AGameCharacter* gameCharacter, AActor* ownerEnemy) const
{
	// Get PlayerForwardVector
	FVector gameCharacterForward = gameCharacter->GetActorForwardVector();

	// Get EnemyForwardVector
	FVector enemyCharacterForward = GetOwner()->GetActorForwardVector();
	enemyCharacterForward *= -1;
	gameCharacterForward.Z = enemyCharacterForward.Z = 0.0f;

	float angle = FMath::RadiansToDegrees(
		FMathf::ACos(FVector::DotProduct(gameCharacterForward, enemyCharacterForward)));

	// ������̸�, ����� �� �ִ� ������ ���
	return (gameCharacter->GetAttackComponent()->GetBlockState() && angle <= 30.0f)
		?  true : false;

}

void UKnightAttackComponent::CheckAttackArea()
{
	if (!IsValid(SwordMeshComponent)) return;

	FVector checkStartLocation = SwordMeshComponent->GetSocketTransform(SWORD_SOCKET_START).GetLocation();
	FVector checkEndLocation = SwordMeshComponent->GetSocketTransform(SWORD_SOCKET_END).GetLocation();

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());
	TArray<FHitResult> hitResults;

	
	UKismetSystemLibrary::SphereTraceMultiByProfile(
		this,
		checkStartLocation,
		checkEndLocation,
		10.0f,
		TEXT("AttackArea"),
		false,
		actorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		hitResults,
		true);

	bool applyHalfDamage = false;

	for (FHitResult hitResult : hitResults)
	{
		// ������ ��ü ��, GameCharacter ������ ��ü�� ����ϴ�.
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(hitResult.GetActor());

		if (!IsValid(gameCharacter)) return;

		float PlayerCurrentHp = gameCharacter->GetCurrentHp();

		
		AKnightCharacter* knightCharacter = Cast<AKnightCharacter>(GetOwner());

		if (!IsValid(knightCharacter)) return;


		UE_LOG(LogTemp, Warning, TEXT("PlayerCurrentHp = [%f]"), PlayerCurrentHp);

		// �÷��̾� ü���� 0���� ������ ��� ó��
		if (PlayerCurrentHp < 0.0f)
		{
			knightCharacter->PlayerDead();
			return;
		}

		// ���� GameCharacter ��ü�� ������ ���
		if (IsValid(gameCharacter))
		{
			//AKnightCharacter* knightCharacter = Cast<AKnightCharacter>(GetOwner());

			// ���Ǿ����� Ȯ���մϴ�.
			bool isBlocked = IsBlocked(gameCharacter, knightCharacter);


			// ��� ó���� ���
			if (isBlocked)
			{
				// ��Ȯ�� �ð��� ��������� Ȯ���մϴ�.
				float currentTime = GetWorld()->GetTimeSeconds();
				float blockStartedTime = gameCharacter->GetAttackComponent()->GetBlockStartTime();
				applyHalfDamage = currentTime - blockStartedTime > 0.5f;

				knightCharacter->PlayAnimMontage(ParriedAnimMontage);

				// ���� ��
				OnAttackFinished();

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
						EnemyData->Atk * (applyHalfDamage ? 0.5f : 1.0f),
						knightCharacter->GetController(),
						knightCharacter,
						UDamageType::StaticClass());
				}
			}
		}
	}
}

void UKnightAttackComponent::InitializeAttackComponent(UStaticMeshComponent* swordMeshComponent, FEnemyData* enemyData)
{
	SwordMeshComponent = swordMeshComponent;
	EnemyData = enemyData;
}

void UKnightAttackComponent::Attack()
{
	Cast<AKnightCharacter>(GetOwner())->PlayAnimMontage(AttackAnimMontage);

}

void UKnightAttackComponent::OnAttackFinished()
{
	TempDamagedActors.Empty();
}

void UKnightAttackComponent::EnableAttackArea()
{
	IsAttackAreaEnabled = true;
}

void UKnightAttackComponent::DisableAttackArea()
{
	IsAttackAreaEnabled = false;
}

