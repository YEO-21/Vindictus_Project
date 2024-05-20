#include "Component/GolemAttackComponent/GolemAttackComponent.h"

#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"
#include "Actor/EnemyController/Golem/GolemController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"

#include "Structure/EnemyData/EnemyData.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UGolemAttackComponent::UGolemAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GOLEMATTACK_ANIMMONTAGE(
		TEXT("/Script/Engine.AnimMontage'/Game/Ancient_Golem/Animation/AnimMontage_GolemAttack.AnimMontage_GolemAttack'"));

	if (GOLEMATTACK_ANIMMONTAGE.Succeeded())
		AttackAnimMontage = GOLEMATTACK_ANIMMONTAGE.Object;

	

}


void UGolemAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Controller
	GolemController = Cast<AGolemController>(Cast<AGolemCharacter>(GetOwner())->GetController());
}


void UGolemAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnableAttack) GolemController->Attack();
}

void UGolemAttackComponent::Attack(FName sectionName)
{
	AGolemCharacter* golem = Cast<AGolemCharacter>(GetOwner());
	FVector direction = golem->GetActorForwardVector();

	// 공격 애님 몽타주 재생합니다.
	golem->PlayAnimMontage(AttackAnimMontage, 1.0f, sectionName);

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(golem);
	TArray<FHitResult> hitResults;

	// 공격 영역을 체크합니다.
	

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		this, golem->GetActorLocation(), golem->GetActorLocation() + direction * 300.0f,
		200.0f, TEXT("AttackArea"), false,
		actorsToIgnore, EDrawDebugTrace::ForDuration,
		hitResults, true);

	
	for (FHitResult hitResult : hitResults)
	{
		// 감지된 객체 중, GameCharacter 형태의 객체를 얻습니다.
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(hitResult.GetActor());
		if (hitResult.GetActor()->ActorHasTag(TEXT("Floor"))) return;
		if (hitResult.GetActor()->ActorHasTag(TEXT("Golem"))) return;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *hitResult.ToString());
		if (!IsValid(gameCharacter)) return;
		

			

		float PlayerCurrentHp = gameCharacter->GetCurrentHp();

		// 플레이어 체력이 0보다 작으면 사망 처리
		if (PlayerCurrentHp < 0.0f)
		{
			golem->PlayerDead();
			return;
		}

		bool isBlocking = gameCharacter->GetAttackComponent()->GetBlockState();
		float damage = golem->GetEnemyData()->Atk;

		// 대미지를 적용합니다.(방어중이라면 0.5 대미지 적용)
		UGameplayStatics::ApplyDamage(gameCharacter, (isBlocking ? damage * 0.5f : damage), golem->GetController(), golem,
			UDamageType::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Apply Damage"));
	}

	
}

void UGolemAttackComponent::EnableAttackArea()
{
	bEnableAttack = true;
}

void UGolemAttackComponent::DisableAttackArea()
{
	bEnableAttack = false;
}
	

