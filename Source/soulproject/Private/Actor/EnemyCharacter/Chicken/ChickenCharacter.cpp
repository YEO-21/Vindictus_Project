#include "Actor/EnemyCharacter/Chicken/ChickenCharacter.h"
#include "Actor/EnemyController/Chicken/ChickenController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AnimInstance/ChickenCharacter/ChickenCharacterAnimInstance.h"


AChickenCharacter::AChickenCharacter()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_ONHIT(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/AnimalVarietyPack/Chicken/Animations/AnimMontage_OnHit.AnimMontage_OnHit'"));
	if (ANIMMONTAGE_ONHIT.Succeeded())
	{
		OnHitAnimMontage = ANIMMONTAGE_ONHIT.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CHICKEN(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/EnemyCharacter/AnimalVarietyPack/Chicken/Meshes/SK_Chicken.SK_Chicken'"));

	static ConstructorHelpers::FClassFinder<UChickenCharacterAnimInstance> ANIMBP_CHICKEN(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_ChickenCharacter.AnimBP_ChickenCharacter_C'"));


	if (SK_CHICKEN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CHICKEN.Object);
	}

	if (ANIMBP_CHICKEN.Succeeded())
	{
		// 애님 인스턴스 클래스 설정
		GetMesh()->SetAnimInstanceClass(ANIMBP_CHICKEN.Class);
	}


	// 컨트롤러 설정
	SetEnemyController(AChickenController::StaticClass());

	EnemyCode = TEXT("000001");

}

void AChickenCharacter::PossessedBy
(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AChickenCharacter::Tick(float dt)
{
	Super::Tick(dt);

	// 애님 인스턴스 파라미터 갱신
	UpdateAnimInstanceParams();
}

void AChickenCharacter::OnDamaged(AGameCharacter* gameCharacter, float damage)
{
	Super::OnDamaged(gameCharacter, damage);

	if (!IsDead)
	{
		// OnHit 애님 몽타주 재생
		PlayAnimMontage(OnHitAnimMontage);
	}
}

void AChickenCharacter::EnemyRespawn()
{
	Super::EnemyRespawn();

	UE_LOG(LogTemp, Warning, TEXT("ChickCharacter"));

	// 죽었던 위치에 적 캐릭터를 스폰합니다.
	GetWorld()->SpawnActor<AChickenCharacter>(BP_ChickenCharacter, DeadLocation);

}




void AChickenCharacter::UpdateAnimInstanceParams()
{
	UChickenCharacterAnimInstance* animInst = 
		Cast<UChickenCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (!IsValid(animInst)) return;


	// 애님 인스턴스에 속력 적용
	float speed = GetVelocity().Length();
	animInst->SetCurrentSpeed(speed);

	// 사망 상태 갱신
	animInst->SetIsDead(IsDead);
}

