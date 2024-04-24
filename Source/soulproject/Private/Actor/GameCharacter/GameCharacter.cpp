#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Components/StaticMeshComponent.h"
#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"
#include "Component/ZoomableSpringArmComponent/ZoomableSpringArmComponent.h"
#include "Component/PlayerCharacterAnimController/PlayerCharacterAnimController.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"
#include "Component/PlayerCharacterInteractComponent/PlayerCharacterInteractComponent.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../soulproject.h"

#include "Structure/PlayerCharacterData/PlayerCharacterData.h"

AGameCharacter::AGameCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CHARACTER_MESH(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Resources/GirlKnight1/Mesh/SK_GirlKnight1.SK_GirlKnight1'"));

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInstance> ANIMBP_PLAYER_CHARACTER(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/AnimInstance/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SABER(
		TEXT("/Script/Engine.StaticMesh'/Game/Resources/GirlKnight1/Mesh/Weapon/SM_Saber.SM_Saber'"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_HIT(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/GirlKnight1/Animations/AnimMontage_Hit.AnimMontage_Hit'"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ANIMMONTAGE_DEAD(
		TEXT("/Script/Engine.AnimMontage'/Game/Resources/GirlKnight1/Animations/AnimMontage_Dead.AnimMontage_Dead'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_AXE(
		TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_TechAxe/SK_Blade_TechAxe.SK_Blade_TechAxe'"));



	if (ANIMMONTAGE_HIT.Succeeded())
	{
		HitAnimMontage = ANIMMONTAGE_HIT.Object;
	}

	if (ANIMMONTAGE_DEAD.Succeeded())
		DeadAnimMontage = ANIMMONTAGE_DEAD.Object;
	



	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 추가
	SpringArmComponent = CreateDefaultSubobject<UZoomableSpringArmComponent>(
		TEXT("SPRING_ARM"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	PlayerCharacterMovementComponent =
		CreateDefaultSubobject<UPlayerCharacterMovementComponent>(TEXT("MOVEMENT_COMPONENT"));

	PlayerCharacterAnimController =
		CreateDefaultSubobject<UPlayerCharacterAnimController>(TEXT("PLAYER_CHARACTER_ANIM_CONTROLLER"));

	AttackComponent =
		CreateDefaultSubobject<UPlayerCharacterAttackComponent>(TEXT("PLAYER_CHARACTER_ATTACK_COMPONENT"));

	InteractComponent =
		CreateDefaultSubobject<UPlayerCharacterInteractComponent>(TEXT("PLAYER_INTERACT_COMPONENT"));

	WeaponMesh =
		CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON_MESH"));

	SubWeaponMesh =
		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SUB_WEAPON_MESH"));




	// SpringArm 컴포넌트를 루트 컴포넌트에 추가합니다.
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);

	// 컨트롤러 Yaw 회전 사용 X
	bUseControllerRotationYaw = false;

	// 무브먼트 방향으로 회전 사용
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도 설정
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	// 스프링암의 회전을 컨트롤러의 회전으로 일치시킵니다.
	SpringArmComponent->bUsePawnControlRotation = true;

	// 캐릭터 SkeletaMesh 설정
	if (SK_CHARACTER_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CHARACTER_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(
			FVector::DownVector * 88.0f,
			FRotator(0.0f, -90.0f, 0.0f));
	}

	// 애니메이션 블루프린트 설정
	if (ANIMBP_PLAYER_CHARACTER.Succeeded())
	{
		GetMesh()->SetAnimClass(ANIMBP_PLAYER_CHARACTER.Class);
	}

	// 무기 붙이기
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("Socket_Weapon"));
	SubWeaponMesh->SetupAttachment(GetMesh(), TEXT("Socket_SubWeapon"));

	if (SM_SABER.Succeeded())
	{
		WeaponMesh->SetStaticMesh(SM_SABER.Object);
		WeaponMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	}

	if (SK_AXE.Succeeded())
	{
		SubWeaponMesh->SetSkeletalMesh(SK_AXE.Object);
		SubWeaponMesh->SetVisibility(false);
		SubWeaponMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}

	// 플레이어 캐릭터의 팀을 설정합니다.
	SetGenericTeamId(FGenericTeamId(ECharacterTeam::Player));

	// 피해 이벤트 설정
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnDamaged);
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 시작 위치를 저장합니다.
	StartLocation = GetActorLocation();

	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(
		GetMesh()->GetAnimInstance());

	PlayerCharacterAnimController->SetAnimInstance(animInst);

	// 걷기로 시작되도록 합니다.
	OnRunStarted();
	OnRunFinished();

	// 다음 공격 입력 확인 시작 이벤트 설정
	PlayerCharacterAnimController->onNextAttackInputCheckStarted.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::StartCheckingNextAttackInput);

	// 다음 공격 입력 확인 끝 이벤트 설정
	PlayerCharacterAnimController->onNextAttackInputCheckFinished.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::FinishCheckingNextAttackInput);

	// 공격 영역 활성화/비활성화 이벤트 설정
	PlayerCharacterAnimController->onAttackAreaEnabled.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::EnableAttackArea);
	PlayerCharacterAnimController->onAttackAreaDisabled.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::DisableAttackArea);

	// 이동 제어를 위한 이벤트 설정
	PlayerCharacterAnimController->onAllowMovementInput.BindUObject(
		PlayerCharacterMovementComponent, &UPlayerCharacterMovementComponent::SetAllowMovementInput);
	PlayerCharacterAnimController->onRollAnimFinished.BindUObject(
		PlayerCharacterMovementComponent, &UPlayerCharacterMovementComponent::OnRollFinished);
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 무기 소켓 위치 갱신
	AttackComponent->UpdateWeaponSocketLocation(WeaponMesh);

	
}

void AGameCharacter::OnDamaged(
	AActor* damagedActor, 
	float damage, 
	const UDamageType* damageType, 
	AController* instigatedBy, 
	AActor* damageCauser)
{
	if (PlayerCharacterMovementComponent->GetRollingState()) return;
	if (IsDead) return;

	// 컨트롤러에게 피해입음 알림
	AGamePlayerController* playerController = Cast<AGamePlayerController>(GetController());
	playerController->OnDamaged(damage);

	//CurrentHp = playerController->GetCurrentHp();


	// 맞는 애니메이션 재생
	if(!IsDead)
	PlayAnimMontage(HitAnimMontage, 1.0f, TEXT("Default"));

	// 피해를 입는 상태로 설정
	IsHit = true;
	PlayerCharacterMovementComponent->OnHit();



	// 방향
	FVector knockBackDirection = (GetActorLocation() - damageCauser->GetActorLocation());
	knockBackDirection.Z = 5.0f;
	knockBackDirection.GetSafeNormal();

	UE_LOG(LogTemp, Warning, TEXT("IsDead is [%d]"), IsDead);

	// 넉백시킵니다.
	if (!IsDead)
		Knockback(knockBackDirection * 10.0f, damage);

	


}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacter::OnPlayerCharacterDataUpdated(const FPlayerCharacterData* const playerCharacterData)
{
	AttackComponent->UpdateAtk(playerCharacterData->Atk);
}

void AGameCharacter::OnHorizontalInput(float axis)
{
	PlayerCharacterMovementComponent->HorizontalMove(axis);
}

void AGameCharacter::OnVerticalInput(float axis)
{
	PlayerCharacterMovementComponent->VerticalMove(axis);
}

void AGameCharacter::OnZoomInput(float axis)
{
	SpringArmComponent->ZoomCamera(axis);
}

void AGameCharacter::OnJumpInput()
{
	// 방어중이라면 함수 호출 종료.
	if (AttackComponent->GetBlockState()) return;

	// 공격중이라면 함수 호출 종료.
	if (AttackComponent->GetAttackState()) return;

	// 구르기중이라면 함수 호출 종료
	if (PlayerCharacterMovementComponent->GetRollingState()) return;

	// 피해를 입는 중이라면 함수 호출 종료
	if (GetHitState()) return;

	PlayerCharacterMovementComponent->OnJump();
}

void AGameCharacter::OnAttackInput()
{
	// 방어중이라면 함수 호출 종료.
	if (AttackComponent->GetBlockState()) return;

	// 구르기중이라면 함수 호출 종료
	if (PlayerCharacterMovementComponent->GetRollingState()) return;

	// 점프 중이라면 함수 호출 종료
	if (GetCharacterMovement()->IsFalling()) return;

	// 피해를 입는 중이라면 함수 호출 종료
	if (GetHitState()) return;

	AttackComponent->RequestAttack(DEFAULT_ATTACK_KEYWORD);
}

void AGameCharacter::OnInteractInput()
{
	// 구르기중이라면 함수 호출 종료.
	if (GetPlayerCharacterMovementComponent()->GetRollingState()) return;
	// 점프중인 경우 함수 호출 종료.
	if (GetMovementComponent()->IsFalling()) return;
	// 공격중인 경우 호출 종료.
	if (GetAttackComponent()->GetAttackState()) return;
	// 피해를 입고 있는 경우 호출 종료.
	if (GetHitState()) return;
	// 방어중인 경우 호출 종료
	if (GetAttackComponent()->GetBlockState()) return;

	// 상호작용 시도
	InteractComponent->TryInteraction();
}

void AGameCharacter::OnRollForward()
{
	PlayerCharacterMovementComponent->OnRollInput(FIntVector2(0, 1));
}

void AGameCharacter::OnRollBackward()
{
	PlayerCharacterMovementComponent->OnRollInput(FIntVector2(0, -1));
}

void AGameCharacter::OnRollRight()
{
	PlayerCharacterMovementComponent->OnRollInput(FIntVector2(1, 0));
}

void AGameCharacter::OnRollLeft()
{
	PlayerCharacterMovementComponent->OnRollInput(FIntVector2(-1, 0));
}

void AGameCharacter::OnBlockStarted()
{
	// 점프중인 경우 함수 호출 종료
	if (GetCharacterMovement()->IsFalling()) return;

	// 구르기중인 경우 함수 호출 종료
	if (PlayerCharacterMovementComponent->GetRollingState()) return;

	// 공격중인 경우 함수 호출 종료
	if (AttackComponent->GetAttackState()) return;

	// 피해를 입는 중이라면 함수 호출 종료
	if (GetHitState()) return;

	// 방어 시작
	AttackComponent->OnBlockStarted();

	// 이동 입력을 블록시킵니다.
	PlayerCharacterMovementComponent->SetAllowMovementInput(false);
}

void AGameCharacter::OnBlockFinished()
{
	if (AttackComponent->GetBlockState())
	{
		AttackComponent->OnBlockFinished();

		// 이동 입력을 허용합니다.
		PlayerCharacterMovementComponent->SetAllowMovementInput(true);
	}
}

void AGameCharacter::OnRunStarted()
{
	PlayerCharacterMovementComponent->OnRunStarted();
}

void AGameCharacter::OnRunFinished()
{
	if (PlayerCharacterMovementComponent->GetRunState())
	{
		PlayerCharacterMovementComponent->OnRunFinished();
	}
}

void AGameCharacter::OnStaminaEmpty()
{
	OnRunFinished();
}

void AGameCharacter::OnHitFinished()
{
	IsHit = false;
}

void AGameCharacter::OnWeaponChanged()
{
	++WeaponCount;
	if ((WeaponCount %2) != 0)
	{
		WeaponMesh->SetVisibility(false);
		SubWeaponMesh->SetVisibility(true);
	}
	else
	{
		WeaponMesh->SetVisibility(true);
		SubWeaponMesh->SetVisibility(false);
	}

	
}

void AGameCharacter::PlayAttackBlockAnim()
{
	PlayAnimMontage(HitAnimMontage, 1.0f, TEXT("AttackBlock"));
	PlayerCharacterMovementComponent->SetAllowMovementInput(false);
}


void AGameCharacter::Knockback(FVector direction, float power)
{
	PlayerCharacterMovementComponent->AddImpulse(direction, power);
}

void AGameCharacter::DeadBounce()
{
	GetCharacterMovement()->Velocity = FVector::ZeroVector;

	GetMesh()->SetCollisionProfileName(TEXT("AttackBlock"));
	GetMesh()->SetSimulatePhysics(true);

	FVector forwardVector = (GetActorForwardVector()*-1.0f) + GetActorUpVector()*1.0f;
	forwardVector.Normalize();
	
	SetActorLocation((GetActorLocation() + GetActorUpVector() * 10.0f));


	// 사망 시 넉백
	Knockback(forwardVector, 100000.0f);
	UE_LOG(LogTemp, Warning, TEXT("DeadBounce is Called!"));

	

}

void AGameCharacter::SetCurrentHp(float currenthp)
{
	CurrentHp = currenthp;
}
