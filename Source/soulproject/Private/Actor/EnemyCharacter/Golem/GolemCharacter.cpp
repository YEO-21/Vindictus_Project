#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"

#include "Actor/EnemyController/Golem/GolemController.h"

AGolemCharacter::AGolemCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));

	if (SK_GOLEM.Succeeded()) GetMesh()->SetSkeletalMesh(SK_GOLEM.Object);


	// 골렘 컨트롤러 설정
	SetEnemyController(AGolemController::StaticClass());

	// 적 코드 설정
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
