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
		// �ִ� �ν��Ͻ� Ŭ���� ����
		GetMesh()->SetAnimInstanceClass(ANIMBP_CHICKEN.Class);
	}


	// ��Ʈ�ѷ� ����
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

	// �ִ� �ν��Ͻ� �Ķ���� ����
	UpdateAnimInstanceParams();
}

void AChickenCharacter::OnDamaged(AGameCharacter* gameCharacter, float damage)
{
	Super::OnDamaged(gameCharacter, damage);

	if (!IsDead)
	{
		// OnHit �ִ� ��Ÿ�� ���
		PlayAnimMontage(OnHitAnimMontage);
	}
}

void AChickenCharacter::EnemyRespawn()
{
	Super::EnemyRespawn();

	UE_LOG(LogTemp, Warning, TEXT("ChickCharacter"));

	// �׾��� ��ġ�� �� ĳ���͸� �����մϴ�.
	GetWorld()->SpawnActor<AChickenCharacter>(BP_ChickenCharacter, DeadLocation);

}




void AChickenCharacter::UpdateAnimInstanceParams()
{
	UChickenCharacterAnimInstance* animInst = 
		Cast<UChickenCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (!IsValid(animInst)) return;


	// �ִ� �ν��Ͻ��� �ӷ� ����
	float speed = GetVelocity().Length();
	animInst->SetCurrentSpeed(speed);

	// ��� ���� ����
	animInst->SetIsDead(IsDead);
}

