#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"
#include "Actor/EnemyController/Golem/GolemController.h"

#include "Component/GolemAttackComponent/GolemAttackComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AnimInstance/GolemCharacter/GolemCharacterAnimInstance.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AGolemCharacter::AGolemCharacter()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM_MOVINGWHEEL(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GOLEM_HEAD(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Ancient_Golem/Mesh/SK_Ancient_Golem_Head_Wheel.SK_Ancient_Golem_Head_Wheel'"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIM_GOLEMHIT(
		TEXT("/Script/Engine.AnimMontage'/Game/Ancient_Golem/Animation/AnimMontage_GolemHit.AnimMontage_GolemHit'"));

		if (SK_GOLEM.Succeeded()) GetMesh()->SetSkeletalMesh(SK_GOLEM.Object);

	// 골렘 휠, 머리 스켈레탈 메시 컴포넌트 추가
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

	if (ANIM_GOLEMHIT.Succeeded())
		HitGolemAnim = ANIM_GOLEMHIT.Object;

	DefaultSceneComponent =
		CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE"));

	SetRootComponent(DefaultSceneComponent);
	GetCapsuleComponent()->SetupAttachment(DefaultSceneComponent);
	
	// 골렘 공격 컴포넌트 추가
	GolemAttackComponent =
		CreateDefaultSubobject<UGolemAttackComponent>(TEXT("GOLEM_ATTACK_COMP"));


	// 골렘 공격 영역 컴포넌트 추가
	GolemAggressiveArea =
		CreateDefaultSubobject<USphereComponent>(TEXT("GOLEM_AREA"));

	GolemAggressiveArea->SetupAttachment(GetRootComponent());

	// 영역 반지름 설정
	GolemAggressiveArea->SetSphereRadius(450.0f);

	GolemAggressiveArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	GolemAggressiveArea->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnEndOverlap);

	GolemAggressiveArea->SetCollisionProfileName(TEXT("NoCollision"));




	// 적 코드 설정
	EnemyCode = TEXT("000005");

	// 골렘 컨트롤러 설정
	SetEnemyController(AGolemController::StaticClass());

	// 메시 콜리전 설정
	GetMesh()->SetCollisionProfileName(TEXT("BlockAllDynamic"), false);

}


void AGolemCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


}

void AGolemCharacter::OnDamaged(AGameCharacter* gameCharacter, float damage)
{
	Super::OnDamaged(gameCharacter, damage);

	// 피격 애니메이션 몽타주 재생
	PlayAnimMontage(HitGolemAnim);

	FVector direction = GetActorForwardVector() * -1.0f;
	
	// 넉백 적용
	LaunchCharacter(direction, 100.0f);



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
		// 골렘 컨트롤러를 얻습니다.
		AGolemController* golemController =
			Cast<AGolemController>(Cast<AGolemCharacter>(OverlappedComponent->GetOwner())->GetController());

		if (!IsValid(golemController)) return;

		UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap"));
		// 공격적 상태를 활성화 합니다.
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
		// 골렘 컨트롤러를 얻습니다.
		AGolemController* golemController =
			Cast<AGolemController>(Cast<AGolemCharacter>(OverlappedComponent->GetOwner())->GetController());



		if (!IsValid(golemController)) return;

		// 공격적 상태를 비활성화 합니다.
		golemController->SetAggressive(false, OtherActor);


	}
}

