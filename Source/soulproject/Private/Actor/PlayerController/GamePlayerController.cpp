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

	// ���� �� �Է� �̺�Ʈ ���ε�
	InputComponent->BindAxis(TEXT("VerticalMove"), this,
		&ThisClass::OnVerticalMovementInput);

	// ���� �� �Է� �̺�Ʈ ���ε�
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

	// �����ϴ� GameCharacter ��ü�� ����ϴ�.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(pawn);
	if (!IsValid(gameCharacter)) return;
	


	// �÷��̾� ĳ���� ������ ����ϴ�.
	FString contextString;
	PlayerCharacterData = PlayerCharacterDataTable->FindRow<FPlayerCharacterData>(
		PLAYERCHARACTER_DATA_NORMAL, contextString);

	// Hp, Stamina �ʱ�ȭ
	CurrentHp = PlayerCharacterData->MaxHp;
	CurrentStamina = PlayerCharacterData->MaxStamina;

	// GameCharacter ���� ���Ǵ� ĳ���� ������ ����
	gameCharacter->OnPlayerCharacterDataUpdated(PlayerCharacterData);

	


	// GameWidget ����
	GameWidget = CreateWidget<UGameWidget>(this, GameWidgetClass);

	// ������ ������ ȭ�鿡 ǥ���մϴ�.
	GameWidget->AddToViewport();

	// �÷��̾� ĳ���� ���� ���� �ʱ�ȭ
	InitializePlayerStateWidget(PlayerCharacterData->MaxHp, PlayerCharacterData->MaxStamina);
	
}

void AGamePlayerController::UpdateStamina(float dt)
{
	// �����ϴ� GameCharacter ��ü�� ����ϴ�.
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetPawn());
	if (!IsValid(gameCharacter)) return;

	// ���� ��ġ�� ����ϴ�.
	FVector currentLocation = gameCharacter->GetActorLocation();

	

	// �޸��� �������� �˻��մϴ�.
	if (gameCharacter->GetPlayerCharacterMovementComponent()->GetRunState())
	{
		// ���� ��ġ�� �Ÿ� Ȯ��
		float moveDistance = FVector::Distance(currentLocation, PrevCharacterLocation);
		CurrentStamina -= moveDistance * 0.5f;
	}
	// �޸��� ���°� �ƴ� ���
	else
	{
		// ���¹̳� ä���
		CurrentStamina += 200.0f * dt;
	}

	// ���¹̳ʸ� ��� ������ ���
	if (CurrentStamina < 0.0f)
	{
		gameCharacter->OnStaminaEmpty();
	}


	// ���¹̳� ��ġ �ּ�, �ִ�� ���α�
	CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, PlayerCharacterData->MaxStamina);


	// Widget ����
	UPlayerStateWidget* playerStateWidget = GameWidget->GetPlayerStateWidget();
	if (IsValid(playerStateWidget))
	{
		playerStateWidget->UpdateStamina(CurrentStamina);
	}

	// ���� ��ġ�� ���
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
	// ��Ʈ�ѷ� Yaw ȸ������ axis ���� ���մϴ�.
	AddYawInput(axis);
}

void AGamePlayerController::OnMouseYInput(float axis)
{
	// ��Ʈ�ѷ� Pitch ȸ������ axis ���� ���մϴ�.
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

	// ���� ���ط� ���
	float hitDamage = (damage - (PlayerCharacterData->Def / 2));
	if (hitDamage < 0.0f) hitDamage = 1;

	// HP ��ġ ����
	CurrentHp -= hitDamage;
	playerStateWidget->UpdateHp(CurrentHp);

	// ��� ó��
	if (CurrentHp <= 0.0f)
	{
		CurrentHp = 0.0f;
		// ��� ó��
	}
}

void AGamePlayerController::OnEnemyAttack(AEnemyCharacter* newTargetEnemy)
{
	GameWidget->ShowEnemyState(newTargetEnemy);
}
