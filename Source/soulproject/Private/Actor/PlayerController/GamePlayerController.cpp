#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Actor/EnemyController/EnemyController.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "Widget/GameWidget/GameWidget.h"
#include "Widget/PlayerStateWidget/PlayerStateWidget.h"
#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"
#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"
#include "Structure/PlayerCharacterData/PlayerCharacterData.h"
#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"

#include "Object/CameraShake/AttackCameraShake.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../soulproject.h"


AGamePlayerController::AGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<UGameWidget> WIDGETBP_GAME(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/GameWidget/WidgetBP_Game.WidgetBP_Game_C'"));

	static ConstructorHelpers::FClassFinder<UNpcDialogWidget> WIDGETBP_DIALOG(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/NpcDialogWidget/WidgetBP_NpcDIalog.WidgetBP_NpcDialog_C'"));

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PLAYERCHARACTERDATA(
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_PlayerCharacterData.DT_PlayerCharacterData'"));

	static ConstructorHelpers::FClassFinder<UPlayerWeaponStateWidget> WIDGETBP_WEAPONSTATE(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/PlayerWeaponStateWiddget/WidgetBP_PlayerWeaponState.WidgetBP_PlayerWeaponState_C'"));

	if (WIDGETBP_GAME.Succeeded())
	{
		GameWidgetClass = WIDGETBP_GAME.Class;
	}

	if (WIDGETBP_DIALOG.Succeeded())
	{
		DialogWidgetClass = WIDGETBP_DIALOG.Class;
	}

	if (DT_PLAYERCHARACTERDATA.Succeeded())
	{
		PlayerCharacterDataTable = DT_PLAYERCHARACTERDATA.Object;
	}

	if (WIDGETBP_WEAPONSTATE.Succeeded())
	{
		WeaponStateWidgetClass = WIDGETBP_WEAPONSTATE.Class;
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

	//InputComponent->BindAction(TEXT("WeaponChange"), EInputEvent::IE_Pressed, this,
	//	&ThisClass::OnWeaponChangePressed);

	InputComponent->BindAction(TEXT("Next"), EInputEvent::IE_Pressed, this,
		&ThisClass::ProgressDialog);

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

	// DialogWidget ����
	DialogWidget = CreateWidget<UNpcDialogWidget>(this, DialogWidgetClass);

	// GameWidget ����
	GameWidget = CreateWidget<UGameWidget>(this, GameWidgetClass);

	WeaponStateWidget = CreateWidget<UPlayerWeaponStateWidget>(this, WeaponStateWidgetClass);

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

void AGamePlayerController::OnWeaponChangePressed()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnWeaponChanged();
	
}

void AGamePlayerController::ProgressDialog()
{
	UE_LOG(LogTemp, Warning, TEXT("DialogNumber is %d"), DialogWidget->DialogNumber);
	++(DialogWidget->DialogNumber);
}

UGameWidget* AGamePlayerController::GetGameWidget() const
{
	return GameWidget;
}

UPlayerWeaponStateWidget* AGamePlayerController::GetWeaponStateWidget() const
{
	return WeaponStateWidget;
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

	// ī�޶� ����ũ ����
	ClientStartCameraShake(UAttackCameraShake::StaticClass());

   

	UPlayerStateWidget* playerStateWidget = GameWidget->GetPlayerStateWidget();

	// Get PlayerCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());

	// ���� ���ط� ���
	float hitDamage = (damage - (PlayerCharacterData->Def / 2));
	if (hitDamage < 0.0f) hitDamage = 1;

	// HP ��ġ ����
	CurrentHp -= hitDamage;
	UE_LOG(LogTemp, Warning, TEXT("CurrentHp = %.2f"), CurrentHp);
	playerStateWidget->UpdateHp(CurrentHp);
	Cast<AGameCharacter>(GetPawn())->SetCurrentHp(CurrentHp);

	// ��� ó��
	if (CurrentHp <= 0.0f && !playerCharacter->GetDeadState())
	{
		// �÷��̾� ��� �ð� ���
		playerCharacter->SetPlayerDeadTime(GetWorld()->GetTimeSeconds());

		playerCharacter->SetDeadState(true);

		CurrentHp = 0.0f;

		// ����� ƨ���� ���� ó��
		playerCharacter->DeadBounce();

		UPlayerCharacterAnimInstance* animInst =
			Cast<UPlayerCharacterAnimInstance>(playerCharacter->GetMesh()->GetAnimInstance());

		if (!IsValid(animInst)) return;

		// ��� ó�� �ִϸ��̼� ���
		animInst->SetPlayerDeadState(true);

		// ��� �� ī�޶� ��ȯ
		playerCharacter->SetCameraDeadView();

		// ��� �� ���� ���� ���� ǥ�� 
		GameWidget->ShowDeadWidget();
		
	}
}

void AGamePlayerController::OnEnemyAttack(AEnemyCharacter* newTargetEnemy)
{
	GameWidget->ShowEnemyState(newTargetEnemy);
}

void AGamePlayerController::ResetPlayerCharacterWidget()
{
	// �÷��̾� ĳ���� ������ ����ϴ�.
	FString contextString;
	PlayerCharacterData = PlayerCharacterDataTable->FindRow<FPlayerCharacterData>(
		PLAYERCHARACTER_DATA_NORMAL, contextString);

	// �÷��̾� ĳ���� ���� ���� �ʱ�ȭ
	InitializePlayerStateWidget(PlayerCharacterData->MaxHp, PlayerCharacterData->MaxStamina);

	// �ִ� ü�� & ���׹̳� ����
	CurrentHp = PlayerCharacterData->MaxHp;
	CurrentStamina = PlayerCharacterData->MaxStamina;

	
}

