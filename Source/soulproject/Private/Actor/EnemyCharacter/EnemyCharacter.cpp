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

	// 컴포넌트 추가
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETCOMPONENT"));
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetRelativeLocation(FVector::UpVector * 50.0f);

	// 컨트롤러 설정
	SetEnemyController(AEnemyController::StaticClass());

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 위젯 클래스 설정
	WidgetComponent->SetWidgetClass(EnemyData->EnemyHUDClass);
	UEnemyWidget* enemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetUserWidgetObject());

	// 적 위젯 객체 초기화
	enemyWidget->InitializeEnemyWidget(EnemyData->Name, EnemyData->MaxHP);

	// 대미지 이벤트 설정
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnDamaged);
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 적 정보 초기화
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

	// 메터리얼 파라미터 설정
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
	// 사망 후 캐릭터가 통과할 수 있도록 컬리전 프리셋 설정
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	// 메터리얼 설정
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

	// 마지막으로 공격받은 시간을 기록합니다.
	LastDamagedTime = UGameplayStatics::GetTimeSeconds(this);

	UEnemyWidget* enemyWidget = Cast<UEnemyWidget>(WidgetComponent->GetUserWidgetObject());

	if (IsValid(enemyWidget))
	{
		// HUD 표시 타이머가 작동중인 경우, 중단시킵니다.
		if (HUDShowTimerHandle.IsValid()) GetWorldTimerManager().ClearTimer(HUDShowTimerHandle);

		// HUD 표시
		enemyWidget->ShowWidget();
		
		// 10 초 이후 HUD 가 숨겨지도록 합니다.
		GetWorldTimerManager().SetTimer(HUDShowTimerHandle, enemyWidget, &UEnemyWidget::HideWidget, 10.0f, false);

		// 현재 체력을 Widget 에 설정합니다.
		enemyWidget->SetHp(CurrentHp);
	}

	//Cast<UEnemyWidget>(WidgetComponent->GetUserWidgetObject())->SetHp(CurrentHp);

	// 체력이 0 미만이 되는 겨우
	if (CurrentHp <= 0.0f)
	{
		CurrentHp = 0.0f;

		// 사망 이벤트 실행
		AEnemyController* enemyController = Cast<AEnemyController>(GetController());

		enemyController->OnDead();
		OnDead();

	}
}

void AEnemyCharacter::OnDead()
{
	// 사망 상태 설정
	IsDead = true;

	// 위젯 객체 제거
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

