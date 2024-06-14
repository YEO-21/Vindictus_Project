#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Actor/EnemyController/Dragon/DragonController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Component/DragonCharacterMovementComponent/DragonCharacterMovementComponent.h"
#include "Component/DragonCharacterAttackComponent/DragonCharacterAttackComponent.h"

#include "AnimInstance/DragonCharacter/DragonCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ADragonCharacter::ADragonCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/EnemyCharacter/DesertDragon/Meshes/SK_DesertDragon.SK_DesertDragon'"));
	if (SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	static ConstructorHelpers::FClassFinder<UDragonCharacterAnimInstance> ANIMBP_DRAGON(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_DragonCharacter.AnimBP_DragonCharacter_C'"));
	if (ANIMBP_DRAGON.Succeeded())
	{
		GetMesh()->SetAnimClass(ANIMBP_DRAGON.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_MOVE(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/DesertDragon/Animations/AnimMontage/AnimMontage_Move.AnimMontage_Move'"));
	if (ANIMMONTAGE_MOVE.Succeeded())
	{
		MoveAnimMontage = ANIMMONTAGE_MOVE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_ATTACK(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/EnemyCharacter/DesertDragon/Animations/AnimMontage/AnimMontage_Attack.AnimMontage_Attack'"));
	if (ANIMMONTAGE_ATTACK.Succeeded())
	{
		AttackAnimMontage = ANIMMONTAGE_ATTACK.Object;
	}


	LeftForwardLeg = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LFLEG"));
	LeftForwardLeg->SetupAttachment(GetMesh(), TEXT("Socket_LFLeg"));

	LeftBackwardLeg = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LBLEG"));
	LeftBackwardLeg->SetupAttachment(GetMesh(), TEXT("Socket_LBLeg"));

	RightForwardLeg = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RFLEG"));
	RightForwardLeg->SetupAttachment(GetMesh(), TEXT("Socket_RFLeg"));

	RightBackwardLeg = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RBLEG"));
	RightBackwardLeg->SetupAttachment(GetMesh(), TEXT("Socket_RBLeg"));

	DragonMovementComponent = CreateDefaultSubobject<UDragonCharacterMovementComponent>(TEXT("MOVEMENT_COMP"));
	AttackComponent = CreateDefaultSubobject<UDragonCharacterAttackComponent>(TEXT("ATTACK_COMP"));
		
	// 컨트롤러 설정
	SetEnemyController(ADragonController::StaticClass());

	// 적 코드 설정
	EnemyCode = TEXT("000004");

	// 이동 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
}


void ADragonCharacter::BeginPlay()
{
	Super::BeginPlay();

	ADragonController * dragonController = Cast<ADragonController>(GetController());

	// 현재 체력 설정
	dragonController->UpdateCurrentHp(CurrentHp);

	UDragonCharacterAnimInstance * animInst = Cast<UDragonCharacterAnimInstance>(
		GetMesh()->GetAnimInstance());

	animInst->OnTurn.AddUObject(DragonMovementComponent, &UDragonCharacterMovementComponent::StartTurn);
	animInst->OnDashFinished.AddUObject(dragonController, &ADragonController::OnDashFinished);

	animInst->OnBreathFireStarted.AddUObject(AttackComponent, &UDragonCharacterAttackComponent::StartBreathFire);
	animInst->OnBreathFireFinished.AddUObject(AttackComponent, &UDragonCharacterAttackComponent::OnBreathFireFinished);

	animInst->OnClawAttackStarted.AddUObject(AttackComponent, &UDragonCharacterAttackComponent::StartClawAttack);
	animInst->OnClawAttackFinished.AddUObject(AttackComponent, &UDragonCharacterAttackComponent::FinishClawAttack);

	animInst->OnRushAttackStarted.AddUObject(AttackComponent, &UDragonCharacterAttackComponent::StartRushAttack);
	animInst->OnRushAttackFinished.AddUObject(AttackComponent, &UDragonCharacterAttackComponent::FinishRushAttack);

	GetMesh()->SetCollisionProfileName(TEXT("EnemyCharacter"));
}

void ADragonCharacter::PlayMoveAnimMontage(FName playSectionName)
{
	PlayAnimMontage(MoveAnimMontage, 1.0f, playSectionName);
}

void ADragonCharacter::PlayAttackAnimMontage(FName playSectionName)
{
	PlayAnimMontage(AttackAnimMontage, 1.0f, playSectionName);
}

void ADragonCharacter::OnPlayerCharacterDetected(AGameCharacter* gameCharacter)
{
	Cast<ADragonController>(GetController())->SetPlayerCharacterKey(gameCharacter);
}
