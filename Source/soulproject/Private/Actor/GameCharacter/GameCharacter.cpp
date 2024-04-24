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

	// ������Ʈ �߰�
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




	// SpringArm ������Ʈ�� ��Ʈ ������Ʈ�� �߰��մϴ�.
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);

	// ��Ʈ�ѷ� Yaw ȸ�� ��� X
	bUseControllerRotationYaw = false;

	// �����Ʈ �������� ȸ�� ���
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ȸ�� �ӵ� ����
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	// ���������� ȸ���� ��Ʈ�ѷ��� ȸ������ ��ġ��ŵ�ϴ�.
	SpringArmComponent->bUsePawnControlRotation = true;

	// ĳ���� SkeletaMesh ����
	if (SK_CHARACTER_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CHARACTER_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(
			FVector::DownVector * 88.0f,
			FRotator(0.0f, -90.0f, 0.0f));
	}

	// �ִϸ��̼� �������Ʈ ����
	if (ANIMBP_PLAYER_CHARACTER.Succeeded())
	{
		GetMesh()->SetAnimClass(ANIMBP_PLAYER_CHARACTER.Class);
	}

	// ���� ���̱�
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

	// �÷��̾� ĳ������ ���� �����մϴ�.
	SetGenericTeamId(FGenericTeamId(ECharacterTeam::Player));

	// ���� �̺�Ʈ ����
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnDamaged);
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���� ��ġ�� �����մϴ�.
	StartLocation = GetActorLocation();

	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(
		GetMesh()->GetAnimInstance());

	PlayerCharacterAnimController->SetAnimInstance(animInst);

	// �ȱ�� ���۵ǵ��� �մϴ�.
	OnRunStarted();
	OnRunFinished();

	// ���� ���� �Է� Ȯ�� ���� �̺�Ʈ ����
	PlayerCharacterAnimController->onNextAttackInputCheckStarted.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::StartCheckingNextAttackInput);

	// ���� ���� �Է� Ȯ�� �� �̺�Ʈ ����
	PlayerCharacterAnimController->onNextAttackInputCheckFinished.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::FinishCheckingNextAttackInput);

	// ���� ���� Ȱ��ȭ/��Ȱ��ȭ �̺�Ʈ ����
	PlayerCharacterAnimController->onAttackAreaEnabled.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::EnableAttackArea);
	PlayerCharacterAnimController->onAttackAreaDisabled.BindUObject(
		AttackComponent, &UPlayerCharacterAttackComponent::DisableAttackArea);

	// �̵� ��� ���� �̺�Ʈ ����
	PlayerCharacterAnimController->onAllowMovementInput.BindUObject(
		PlayerCharacterMovementComponent, &UPlayerCharacterMovementComponent::SetAllowMovementInput);
	PlayerCharacterAnimController->onRollAnimFinished.BindUObject(
		PlayerCharacterMovementComponent, &UPlayerCharacterMovementComponent::OnRollFinished);
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ���� ��ġ ����
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

	// ��Ʈ�ѷ����� �������� �˸�
	AGamePlayerController* playerController = Cast<AGamePlayerController>(GetController());
	playerController->OnDamaged(damage);

	//CurrentHp = playerController->GetCurrentHp();


	// �´� �ִϸ��̼� ���
	if(!IsDead)
	PlayAnimMontage(HitAnimMontage, 1.0f, TEXT("Default"));

	// ���ظ� �Դ� ���·� ����
	IsHit = true;
	PlayerCharacterMovementComponent->OnHit();



	// ����
	FVector knockBackDirection = (GetActorLocation() - damageCauser->GetActorLocation());
	knockBackDirection.Z = 5.0f;
	knockBackDirection.GetSafeNormal();

	UE_LOG(LogTemp, Warning, TEXT("IsDead is [%d]"), IsDead);

	// �˹��ŵ�ϴ�.
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
	// ������̶�� �Լ� ȣ�� ����.
	if (AttackComponent->GetBlockState()) return;

	// �������̶�� �Լ� ȣ�� ����.
	if (AttackComponent->GetAttackState()) return;

	// ���������̶�� �Լ� ȣ�� ����
	if (PlayerCharacterMovementComponent->GetRollingState()) return;

	// ���ظ� �Դ� ���̶�� �Լ� ȣ�� ����
	if (GetHitState()) return;

	PlayerCharacterMovementComponent->OnJump();
}

void AGameCharacter::OnAttackInput()
{
	// ������̶�� �Լ� ȣ�� ����.
	if (AttackComponent->GetBlockState()) return;

	// ���������̶�� �Լ� ȣ�� ����
	if (PlayerCharacterMovementComponent->GetRollingState()) return;

	// ���� ���̶�� �Լ� ȣ�� ����
	if (GetCharacterMovement()->IsFalling()) return;

	// ���ظ� �Դ� ���̶�� �Լ� ȣ�� ����
	if (GetHitState()) return;

	AttackComponent->RequestAttack(DEFAULT_ATTACK_KEYWORD);
}

void AGameCharacter::OnInteractInput()
{
	// ���������̶�� �Լ� ȣ�� ����.
	if (GetPlayerCharacterMovementComponent()->GetRollingState()) return;
	// �������� ��� �Լ� ȣ�� ����.
	if (GetMovementComponent()->IsFalling()) return;
	// �������� ��� ȣ�� ����.
	if (GetAttackComponent()->GetAttackState()) return;
	// ���ظ� �԰� �ִ� ��� ȣ�� ����.
	if (GetHitState()) return;
	// ������� ��� ȣ�� ����
	if (GetAttackComponent()->GetBlockState()) return;

	// ��ȣ�ۿ� �õ�
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
	// �������� ��� �Լ� ȣ�� ����
	if (GetCharacterMovement()->IsFalling()) return;

	// ���������� ��� �Լ� ȣ�� ����
	if (PlayerCharacterMovementComponent->GetRollingState()) return;

	// �������� ��� �Լ� ȣ�� ����
	if (AttackComponent->GetAttackState()) return;

	// ���ظ� �Դ� ���̶�� �Լ� ȣ�� ����
	if (GetHitState()) return;

	// ��� ����
	AttackComponent->OnBlockStarted();

	// �̵� �Է��� ��Ͻ�ŵ�ϴ�.
	PlayerCharacterMovementComponent->SetAllowMovementInput(false);
}

void AGameCharacter::OnBlockFinished()
{
	if (AttackComponent->GetBlockState())
	{
		AttackComponent->OnBlockFinished();

		// �̵� �Է��� ����մϴ�.
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


	// ��� �� �˹�
	Knockback(forwardVector, 100000.0f);
	UE_LOG(LogTemp, Warning, TEXT("DeadBounce is Called!"));

	

}

void AGameCharacter::SetCurrentHp(float currenthp)
{
	CurrentHp = currenthp;
}
