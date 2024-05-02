#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"

#include "Actor/EnemyController/Golem/GolemController.h"

AGolemCharacter::AGolemCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));

	if (SK_GOLEM.Succeeded()) GetMesh()->SetSkeletalMesh(SK_GOLEM.Object);


	// �� ��Ʈ�ѷ� ����
	SetEnemyController(AGolemController::StaticClass());

	// �� �ڵ� ����
	EnemyCode = TEXT("000005");




}

void AGolemCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGolemCharacter::Tick(float dt)
{
	Super::Tick(dt);
}
