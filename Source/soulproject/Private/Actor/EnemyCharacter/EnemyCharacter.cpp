#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Actor/EnemyController/EnemyController.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/Chicken/ChickenCharacter.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Success!!"));
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

	// 적 클래스 설정
	SetEnemyClass();

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
			alpha -= 0.6f;
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
	UE_LOG(LogTemp, Warning, TEXT("EnemyCode = [%s]"), *EnemyCode.ToString());
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
	UE_LOG(LogTemp, Warning, TEXT("ChangeMaterialToDeadState"));

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



void AEnemyCharacter::EnemyRespawn()
{
	// 적을 먼저 제거합니다.
	OnEnemyDestroy();

	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()
		{
			// 골렘의 경우, 죽을 때 마다 크기가 3배씩 커지고, 
			// 크기가 27배가 이상이 되면 다시 처음으로 돌아갑니다.
			if (DeadLocation.GetScale3D().X >= 27.0f)
				DeadLocation.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			// 죽은 위치에 리스폰을 합니다.
			GetWorld()->SpawnActor<AEnemyCharacter>(BP_EnemyCharacter, DeadLocation);
			IsDead = false;
		});
	// 3초후 리스폰이 되도록 합니다.
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, timerDelegate, 3.0f, false);


	UE_LOG(LogTemp, Warning, TEXT("EnemyRespawn is called"));
}

void AEnemyCharacter::SetEnemyClass()
{
	BP_EnemyCharacter = ThisClass::StaticClass();
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

		// 현재 사망 위치를 기록합니다.
		DeadLocation = GetActorTransform();

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

	// 사망 시 메터리얼 상태 적용
	//ChangeMaterialToDeadState();

	// 드래곤을 제외한 적 캐릭터는 15초 후 리스폰 하고, 랙돌을 적용합니다.
	if (!(EnemyCode == TEXT("000004")))
	{
		// 리스폰 타이머 설정(5s)
		GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ThisClass::EnemyRespawn, 15.0f, false);

		// 랙돌 적용
		PlayRagdoll();
	}
	

	
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

void AEnemyCharacter::PlayerRespawn()
{
	Cast<AEnemyController>(GetController())->OnPlayerRespawn();
}

