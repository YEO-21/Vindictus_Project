#include "Actor/EnemyCharacter/Wolf/WolfCharacter.h"
#include "Actor/EnemyController/Wolf/WolfController.h"
#include "AnimInstance/WolfCharacter/WolfCharacterAnimInstance.h"
#include "Component/WolfAttackComponent/WolfAttackComponent.h"

#include "Kismet/KismetSystemLibrary.h"

AWolfCharacter::AWolfCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/EnemyCharacter/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'"));

	static ConstructorHelpers::FClassFinder<UWolfCharacterAnimInstance> ANIMBP_WOLF(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_WolfCharacter.AnimBP_WolfCharacter_C'"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMBP_WOLFHIT(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/AnimalVarietyPack/Wolf/Animations/AnimMontage_GetHit.AnimMontage_GetHit'"));


	// 공격 컴포넌트 추가
	AttackComponent = CreateDefaultSubobject<UWolfAttackComponent>(TEXT("ATTACK_COMP"));

	if (SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	if (ANIMBP_WOLF.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIMBP_WOLF.Class);
	}

	if (ANIMBP_WOLFHIT.Succeeded()) HitAnimMontage = ANIMBP_WOLFHIT.Object;

	// 적 코드 설정
	EnemyCode = TEXT("000003");

	// 컨트롤러 설정
	SetEnemyController(AWolfController::StaticClass());



}

void AWolfCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 그룹을 찾습니다.
	FindGroup();
}

void AWolfCharacter::Tick(float dt)
{
	Super::Tick(dt);

	UpdateAnimInstanceParams();
}

void AWolfCharacter::UpdateAnimInstanceParams()
{
	UWolfCharacterAnimInstance* animInst = Cast<UWolfCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (!IsValid(animInst)) return;

	// 속력 갱신
	animInst->SetCurrentSpeed(GetVelocity().Length());
}

void AWolfCharacter::FindGroup()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypeQuery = 
	{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };

	TArray<AActor*> actorsToIgnore;
	TArray<AActor*> findActors;

	if (UKismetSystemLibrary::SphereOverlapActors(
		this, GetActorLocation(), 300.0f,
		objectTypeQuery,
		AWolfCharacter::StaticClass(),
		actorsToIgnore,
		findActors))
	{
		for (AActor* findActor : findActors)
		{
			Group.Add(Cast<AWolfCharacter>(findActor));
		}
	}
}

void AWolfCharacter::GetWolfStateNumber()
{
	// 공격 상태라면 상태 전환을 하지 않습니다.
	AWolfController* wolfController = Cast<AWolfController>(GetController());
	if (wolfController->CheckAggressiveState()) return;

	// Get AnimInstance
	UWolfCharacterAnimInstance* animInst = Cast<UWolfCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (!IsValid(animInst)) return;

	// 0~100 사이의 랜덤값을 얻어 상태를 전환합니다.
	int random = FMath::FRandRange(0.0f, 100.f);
	animInst->SetWolfStateNumber(random);
}

void AWolfCharacter::OnDamaged(AGameCharacter* gameCharacter, float damage)
{
	Super::OnDamaged(gameCharacter, damage);

	// 피격 애니메이션 재생
	PlayAnimMontage(HitAnimMontage);

	FVector direction = GetActorForwardVector() * -1.0f;

	// 넉백 적용
	LaunchCharacter(direction, 1000.0f);

	/*UWolfCharacterAnimInstance* animInst = Cast<UWolfCharacterAnimInstance>(GetMesh()->GetAnimInstance());
 	animInst->SetWolfStateNumber(0.0f);*/

	for (AWolfCharacter* wolfCharacter : Group)
	{
		AWolfController* otherWolfController = Cast<AWolfController>(wolfCharacter->GetController());
		if (!IsValid(otherWolfController)) continue;

		otherWolfController->OnOtherWolfDamaged(gameCharacter);

		UWolfCharacterAnimInstance* OtherWolfanimInst = Cast<UWolfCharacterAnimInstance>(wolfCharacter->GetMesh()->GetAnimInstance());
		if (!IsValid(OtherWolfanimInst)) continue;

		// 공격 상태일 경우, 기본 자세로 전환
		OtherWolfanimInst->SetWolfStateNumber(0.0f);
	}
}
