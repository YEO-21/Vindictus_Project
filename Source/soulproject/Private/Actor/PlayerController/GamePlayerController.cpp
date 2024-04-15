#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Widget/GameWidget/GameWidget.h"
#include "Widget/PlayerStateWidget/PlayerStateWidget.h"
#include "Structure/PlayerCharacterData/PlayerCharacterData.h"
#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"

AGamePlayerController::AGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<UGameWidget> WIDGETBP_GAME(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/GameWidget/WidgetBP_Game.WidgetBP_Game_C'"));

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PLAYERCHARACTERDATA(
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_PlayerCharacterData.DT_PlayerCharacterData'"));

	if (WIDGETBP_GAME.Succeeded())
	{
		GameWidgetClass = WIDGETBP_GAME.Class;
	}

	if (DT_PLAYERCHARACTERDATA.Succeeded())
	{
		PlayerCharacterDataTable = DT_PLAYERCHARACTERDATA.Object;
	}
	PlayerCharacterData = nullptr;
}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateStamina(DeltaTime);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 수직 축 입력 이벤트 바인딩
	InputComponent->BindAxis(TEXT("VerticalMove"), this,
		&ThisClass::OnVerticalMovementInput);

	// 수평 축 입력 이벤트 바인딩
	InputComponent->BindAxis(TEXT("HorizontalMove"), this,
		&ThisClass::OnHorizontalMovementInput);

	InputComponent->BindAxis(TEXT("MouseX"), this,
		&ThisClass::OnMouseXInput);

	InputComponent->BindAxis(TEXT("MouseY"), this,
		&ThisClass::OnMouseYInput);

	InputComponent->BindAxis(TEXT("MouseWheel"), this,
		&ThisClass::OnZoomInput);

	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnJumpInput);

	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnAttackInput);

	InputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnInteractInput);

	InputComponent->BindAction(TEXT("RollForward"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnRollForward);
	InputComponent->BindAction(TEXT("RollBackward"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnRollBackward);
	InputComponent->BindAction(TEXT("RollRight"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnRollRight);
	InputComponent->BindAction(TEXT("RollLeft"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnRollLeft);

	InputComponent->BindAction(TEXT("BlockInput"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnBlockPressed);
	InputComponent->BindAction(TEXT("BlockInput"), EInputEvent::IE_Released, this,
		&ThisClass::OnBlockReleased);

	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnRunPressed);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this,
		&ThisClass::OnRunReleased);

}

void AGamePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	// 조종하는 GameCharacter 객체를 얻습니다.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(pawn);
	if (!IsValid(gameCharacter)) return;
	


	// 플레이어 캐릭터 정보를 얻습니다.
	FString contextString;
	PlayerCharacterData = PlayerCharacterDataTable->FindRow<FPlayerCharacterData>(
		PLAYERCHARACTER_DATA_NORMAL, contextString);

	// Hp, Stamina 초기화
	CurrentHp = PlayerCharacterData->MaxHp;
	CurrentStamina = PlayerCharacterData->MaxStamina;

	// GameCharacter 에서 사용되는 캐릭터 데이터 갱신
	gameCharacter->OnPlayerCharacterDataUpdated(PlayerCharacterData);

	


	// GameWidget 생성
	GameWidget = CreateWidget<UGameWidget>(this, GameWidgetClass);

	// 생성된 위젯을 화면에 표시합니다.
	GameWidget->AddToViewport();

	// 플레이어 캐릭터 상태 위젯 초기화
	InitializePlayerStateWidget(PlayerCharacterData->MaxHp, PlayerCharacterData->MaxStamina);
	
}

void AGamePlayerController::UpdateStamina(float dt)
{
	// 조종하는 GameCharacter 객체를 얻습니다.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetPawn());
	if (!IsValid(gameCharacter)) return;

	// 현재 위치를 얻습니다.
	FVector currentLocation = gameCharacter->GetActorLocation();

	

	// 달리기 상태인지 검사합니다.
	if (gameCharacter->GetPlayerCharacterMovementComponent()->GetRunState())
	{
		// 현재 위치와 거리 확인
		float moveDistance = FVector::Distance(currentLocation, PrevCharacterLocation);
		CurrentStamina -= moveDistance * 0.5f;
	}
	// 달리기 상태가 아닌 경우
	else
	{
		// 스태미너 채우기
		CurrentStamina += 200.0f * dt;
	}

	// 스태미너를 모두 소진한 경우
	if (CurrentStamina < 0.0f)
	{
		gameCharacter->OnStaminaEmpty();
	}


	// 스태미너 수치 최소, 최대로 가두기
	CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, PlayerCharacterData->MaxStamina);


	// Widget 갱신
	UPlayerStateWidget* playerStateWidget = GameWidget->GetPlayerStateWidget();
	if (IsValid(playerStateWidget))
	{
		playerStateWidget->UpdateStamina(CurrentStamina);
	}

	// 이전 위치를 기록
	PrevCharacterLocation = currentLocation;
}

void AGamePlayerController::OnVerticalMovementInput(float axis)
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnVerticalInput(axis);
}

void AGamePlayerController::OnHorizontalMovementInput(float axis)
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnHorizontalInput(axis);
}

void AGamePlayerController::OnMouseXInput(float axis)
{
	// 컨트롤러 Yaw 회전값에 axis 값을 더합니다.
	AddYawInput(axis);
}

void AGamePlayerController::OnMouseYInput(float axis)
{
	// 컨트롤러 Pitch 회전값에 axis 값을 더합니다.
	AddPitchInput(-axis);
}

void AGamePlayerController::OnZoomInput(float axis)
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnZoomInput(axis);
}

void AGamePlayerController::OnJumpInput()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnJumpInput();
}

void AGamePlayerController::OnAttackInput()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnAttackInput();
}

void AGamePlayerController::OnInteractInput()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnInteractInput();
}

void AGamePlayerController::OnRollForward()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnRollForward();
}

void AGamePlayerController::OnRollBackward()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnRollBackward();
}

void AGamePlayerController::OnRollRight()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnRollRight();
}

void AGamePlayerController::OnRollLeft()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnRollLeft();
}

void AGamePlayerController::OnBlockPressed()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnBlockStarted();
}

void AGamePlayerController::OnBlockReleased()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnBlockFinished();
}

void AGamePlayerController::OnRunPressed()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnRunStarted();
}

void AGamePlayerController::OnRunReleased()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnRunFinished();
}

UGameWidget* AGamePlayerController::GetGameWidget() const
{
	return GameWidget;
}

void AGamePlayerController::SetCameraViewTarget(AActor* target)
{
	SetViewTargetWithBlend(target, 0.2f);
}

void AGamePlayerController::ClearCameraViewTarget()
{
	SetViewTargetWithBlend(GetPawn(), 0.2f);
}

void AGamePlayerController::InitializePlayerStateWidget(float maxHp, float maxStamina)
{
	if (!IsValid(GameWidget)) return;

	UPlayerStateWidget* playerStateWidget = GameWidget->GetPlayerStateWidget();
	playerStateWidget->SetMaxHp(maxHp);
	playerStateWidget->UpdateHp(maxHp);
	playerStateWidget->SetMaxStamina(maxStamina);
	playerStateWidget->UpdateStamina(maxStamina);
}

void AGamePlayerController::OnDamaged(float damage)
{
	if (!IsValid(GameWidget)) return;

	UPlayerStateWidget* playerStateWidget = GameWidget->GetPlayerStateWidget();

	// 입힐 피해량 계산
	float hitDamage = (damage - (PlayerCharacterData->Def / 2));
	if (hitDamage < 0.0f) hitDamage = 1;

	// HP 수치 갱신
	CurrentHp -= hitDamage;
	playerStateWidget->UpdateHp(CurrentHp);

	// 사망 처리
	if (CurrentHp <= 0.0f)
	{
		CurrentHp = 0.0f;
		// 사망 처리
	}
}

void AGamePlayerController::OnEnemyAttack(AEnemyCharacter* newTargetEnemy)
{
	GameWidget->ShowEnemyState(newTargetEnemy);
}
