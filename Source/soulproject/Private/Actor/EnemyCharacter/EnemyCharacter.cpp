#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Actor/EnemyController/EnemyController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "Widget/EnemyWidget/EnemyWidget.h"

#include "Structure/EnemyData/EnemyData.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY_DATA(
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_EnemyData.DT_EnemyData'"));
	if (DT_ENEMY_DATA.Succeeded())
	{
		EnemyDataTable = DT_ENEMY_DATA.Object;
	}

	// ������Ʈ �߰�
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETCOMPONENT"));
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetRelativeLocation(FVector::UpVector * 50.0f);

	// ��Ʈ�ѷ� ����
	SetEnemyController(AEnemyController::StaticClass());

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���� Ŭ���� ����
	WidgetComponent->SetWidgetClass(EnemyData->EnemyHUDClass);
	UEnemyWidget* enemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetUserWidgetObject());

	// �� ���� ��ü �ʱ�ȭ
	enemyWidget->InitializeEnemyWidget(EnemyData->Name, EnemyData->MaxHP);

	// ����� �̺�Ʈ ����
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnDamaged);
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// �� ���� �ʱ�ȭ
	InitializeEnemyData();

	if (EnemyData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyData is notValid (EnemyCode : %s)"), *EnemyCode.ToString());
		return;
	}
	else
	{
		AEnemyController* enemyController = Cast<AEnemyController>(NewController);
		enemyController->InitializeEnemyController(EnemyData);
	}




}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���͸��� �Ķ���� ����
	if (IsDead)
	{
		if (IsValid(MaterialInstanceOnDead))
		{
			float alpha;
			MaterialInstanceOnDead->GetScalarParameterValue(TEXT("_Alpha"), alpha);
			alpha -= 1.0f;
			MaterialInstanceOnDead->SetScalarParameterValue(TEXT("_Alpha"), alpha);

			if (alpha <= 0.0f) OnEnemyDestroy();
		}
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::LaunchCharacter(FVector direction, float power)
{
	Super::LaunchCharacter(direction * power, true, false);
}

void AEnemyCharacter::InitializeEnemyData()
{
	if (EnemyCode.IsNone()) return;

	FString contextString;
	EnemyData = EnemyDataTable->FindRow<FEnemyData>(EnemyCode, contextString);

	if (EnemyData != nullptr)
	{
		CurrentHp = EnemyData->MaxHP;

	}
}

void AEnemyCharacter::OnDamaged(
	AActor* DamagedActor, 
	float Damage, 
	const UDamageType* DamageType, 
	AController* InstigatedBy, 
	AActor* DamageCauser)
{
	AEnemyController* enemyController = Cast<AEnemyController>(GetController());
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(DamageCauser);

	if (IsValid(gameCharacter) && IsValid(enemyController))
	{
		float calculatedDamage = CalculateDamage(Damage);
		enemyController->OnDamaged(gameCharacter, calculatedDamage);
		OnDamaged(gameCharacter, calculatedDamage);
	}
}

void AEnemyCharacter::ChangeMaterialToDeadState()
{
	// ��� �� ĳ���Ͱ� ����� �� �ֵ��� �ø��� ������ ����
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	// ���͸��� ����
	MaterialInstanceOnDead = UMaterialInstanceDynamic::Create(
		EnemyData->MaterialInstanceOnDead, this);

	GetMesh()->SetMaterial(0, MaterialInstanceOnDead);
}

void AEnemyCharacter::PlayRagdoll()
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

void AEnemyCharacter::SetEnemyController(
	TSubclassOf<class AEnemyController> controllerClass, 
	EAutoPossessAI possessType)
{
	AIControllerClass = controllerClass;
	AutoPossessAI = possessType;
}

void AEnemyCharacter::OnDamaged(AGameCharacter* gameCharacter, float damage)
{
	CurrentHp -= damage;

	// ���������� ���ݹ��� �ð��� ����մϴ�.
	LastDamagedTime = UGameplayStatics::GetTimeSeconds(this);

	UEnemyWidget* enemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetUserWidgetObject());

	if (IsValid(enemyWidget))
	{
		// HUD ǥ�� Ÿ�̸Ӱ� �۵����� ���, �ߴܽ�ŵ�ϴ�.
		if (HUDShowTimerHandle.IsValid()) GetWorldTimerManager().ClearTimer(HUDShowTimerHandle);

		// HUD ǥ��
		enemyWidget->ShowWidget();
		
		// 10 �� ���� HUD �� ���������� �մϴ�.
		GetWorldTimerManager().SetTimer(HUDShowTimerHandle, enemyWidget, &UEnemyWidget::HideWidget, 10.0f, false);

		// ���� ü���� Widget �� �����մϴ�.
		enemyWidget->SetHp(CurrentHp);
	}

	//Cast<UEnemyWidget>(WidgetComponent->GetUserWidgetObject())->SetHp(CurrentHp);

	// ü���� 0 �̸��� �Ǵ� �ܿ�
	if (CurrentHp <= 0.0f)
	{
		CurrentHp = 0.0f;

		// ��� �̺�Ʈ ����
		AEnemyController* enemyController = Cast<AEnemyController>(GetController());

		enemyController->OnDead();
		OnDead();

	}
}

void AEnemyCharacter::OnDead()
{
	// ��� ���� ����
	IsDead = true;

	// ���� ��ü ����
	WidgetComponent->SetWidget(nullptr);
	if (HUDShowTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(HUDShowTimerHandle);
	}


	PlayRagdoll();
}

void AEnemyCharacter::OnEnemyDestroy()
{
	Destroy();
}

float AEnemyCharacter::CalculateDamage(float damage)
{
	return damage;
}

void AEnemyCharacter::PlayerDead()
{
	Cast<AEnemyController>(GetController())->OnPlayerDead();

}

