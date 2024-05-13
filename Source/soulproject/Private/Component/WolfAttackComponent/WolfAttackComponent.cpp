#include "Component/WolfAttackComponent/WolfAttackComponent.h"

#include "Actor/EnemyCharacter/Wolf/WolfCharacter.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Structure/EnemyData/EnemyData.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UWolfAttackComponent::UWolfAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_ATTACK(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/AnimalVarietyPack/Wolf/Animations/AnimMontage_Attack.AnimMontage_Attack'"));
	if (ANIMMONTAGE_ATTACK.Succeeded())
	{
		AttackAnimMontage = ANIMMONTAGE_ATTACK.Object;
	}

}

void UWolfAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWolfAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWolfAttackComponent::Attack()
{
	Cast<AWolfCharacter>(GetOwner())->PlayAnimMontage(AttackAnimMontage);
	CheckAttackArea();
}

void UWolfAttackComponent::CheckAttackArea()
{
	// wolf ��ü�� ����ϴ�.
	AWolfCharacter* wolf = Cast<AWolfCharacter>(GetOwner());

	// ���� ���� ������ ���� ���� ��ġ�� ����ϴ�.
	FVector wolfAttackStartLocation =
		wolf->GetMesh()->GetSocketTransform(WOLF_SOCKET_START).GetLocation();
	FVector wolfAttackEndLocation =
		wolf->GetMesh()->GetSocketTransform(WOLF_SOCKET_END).GetLocation();

	// �ڽ� �߽ɿ��� �� �������� �Ÿ�
	FVector halfSize = (wolfAttackEndLocation - wolfAttackStartLocation) * 0.5f;

	TArray<AActor*> actorsToIgnore;
	TArray<FHitResult> hitResults;

	// ���� ����(�ڽ�)���� ������ �Ǿ����� Ȯ���մϴ�.
	UKismetSystemLibrary::BoxTraceMultiByProfile(this,
		wolfAttackStartLocation,
		wolfAttackEndLocation,
		halfSize,
		FRotator(1.0f,1.0f, 1.0f),
		TEXT("AttackArea"),
		false,
		actorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		hitResults,
		true);


	for (FHitResult hit : hitResults)
	{
		UE_LOG(LogTemp, Warning, TEXT("ApplyDamage"));
		// �÷��̾� ��ü�� ����ϴ�.
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(hit.GetActor());
			
		if (!IsValid(gameCharacter)) return;

		// �÷��̾� ü���� ����ϴ�.
		float currentPlayerHp = gameCharacter->GetCurrentHp();

			
		// �÷��̾� ü���� 0 ������ ��� ���ó�� �մϴ�.
		if (currentPlayerHp <= 0.0f)
		{
			wolf->PlayerDead();
		}

		// ������� �����մϴ�.
		UGameplayStatics::ApplyDamage(gameCharacter, wolf->GetEnemyData()->Atk, wolf->GetController(), wolf,
			UDamageType::StaticClass());

	}
	




}

