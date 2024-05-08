#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"
#include "Actor/EnemyController/Golem/GolemController.h"

#include "Component/GolemAttackComponent/GolemAttackComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AnimInstance/GolemCharacter/GolemCharacterAnimInstance.h"

#include "Components/SphereComponent.h"

AGolemCharacter::AGolemCharacter()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM_MOVINGWHEEL(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM_HEAD(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Head_Wheel.SK_Ancient_Golem_Head_Wheel'"));


	if (SK_GOLEM.Succeeded()) GetMesh()->SetSkeletalMesh(SK_GOLEM.Object);

	// �� ��, �Ӹ� ���̷�Ż �޽� ������Ʈ �߰�
	GolemMovingWheel =
		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MOVING_WHEEL"));

	GolemHead =
		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GOLEM_HEAD"));


	GolemMovingWheel->SetupAttachment(GetMesh(), TEXT("spine_03Socket"));
	GolemHead->SetupAttachment(GetMesh(), TEXT("headSocket"));

	if (SK_GOLEM_MOVINGWHEEL.Succeeded())
		GolemMovingWheel->SetSkeletalMesh(SK_GOLEM_MOVINGWHEEL.Object);

	if (SK_GOLEM_HEAD.Succeeded())
		GolemHead->SetSkeletalMesh(SK_GOLEM_HEAD.Object);

	
	
	// �� ���� ������Ʈ �߰�
	GolemAttackComponent =
		CreateDefaultSubobject<UGolemAttackComponent>(TEXT("GOLEM_ATTACK_COMP"));


	// �� ���� ���� ������Ʈ �߰�
	GolemAggressiveArea =
		CreateDefaultSubobject<USphereComponent>(TEXT("GOLEM_AREA"));

	GolemAggressiveArea->SetupAttachment(GetRootComponent());

	// ���� ������ ����
	GolemAggressiveArea->SetSphereRadius(450.0f);

	GolemAggressiveArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	GolemAggressiveArea->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnEndOverlap);




	// �� �ڵ� ����
	EnemyCode = TEXT("000005");

	// �� ��Ʈ�ѷ� ����
	SetEnemyController(AGolemController::StaticClass());

	// �޽� �ݸ��� ����
	GetMesh()->SetCollisionProfileName(TEXT("BlockAllDynamic"), false);

}


void AGolemCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


}

void AGolemCharacter::Tick(float dt)
{
	Super::Tick(dt);
}

void AGolemCharacter::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AGameCharacter>())
	{
		// �� ��Ʈ�ѷ��� ����ϴ�.
		AGolemController* golemController =
			Cast<AGolemController>(Cast<AGolemCharacter>(OverlappedComponent->GetOwner())->GetController());
		if (!IsValid(golemController)) return;


		// ������ ���¸� Ȱ��ȭ �մϴ�.
		golemController->SetAggressive(true, OtherActor);


	}


	
}

void AGolemCharacter::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AGameCharacter>())
	{
		// �� ��Ʈ�ѷ��� ����ϴ�.
		AGolemController* golemController =
			Cast<AGolemController>(Cast<AGolemCharacter>(OverlappedComponent->GetOwner())->GetController());



		if (!IsValid(golemController)) return;

		// ������ ���¸� ��Ȱ��ȭ �մϴ�.
		golemController->SetAggressive(false, OtherActor);


	}
}

