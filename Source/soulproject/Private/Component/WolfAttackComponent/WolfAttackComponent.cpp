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
	// wolf 객체를 얻습니다.
	AWolfCharacter* wolf = Cast<AWolfCharacter>(GetOwner());

	// 공격 영역 설정을 위한 소켓 위치를 얻습니다.
	FVector wolfAttackStartLocation =
		wolf->GetMesh()->GetSocketTransform(WOLF_SOCKET_START).GetLocation();
	FVector wolfAttackEndLocation =
		wolf->GetMesh()->GetSocketTransform(WOLF_SOCKET_END).GetLocation();

	// 박스 중심에서 각 변까지의 거리
	FVector halfSize = (wolfAttackEndLocation - wolfAttackStartLocation) * 0.5f;

	TArray<AActor*> actorsToIgnore;
	TArray<FHitResult> hitResults;

	// 공격 영역(박스)내에 감지가 되었는지 확인합니다.
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
		// 플레이어 객체를 얻습니다.
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(hit.GetActor());
			
		if (!IsValid(gameCharacter)) return;

		// 플레이어 체력을 얻습니다.
		float currentPlayerHp = gameCharacter->GetCurrentHp();

			
		// 플레이어 체력이 0 이하일 경우 사망처리 합니다.
		if (currentPlayerHp <= 0.0f)
		{
			wolf->PlayerDead();
		}

		// 대미지를 적용합니다.
		UGameplayStatics::ApplyDamage(gameCharacter, wolf->GetEnemyData()->Atk, wolf->GetController(), wolf,
			UDamageType::StaticClass());

	}
	




}

