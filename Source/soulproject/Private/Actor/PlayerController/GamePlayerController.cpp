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
#include "Widget/PlayerStateSlotWidget/PlayerStateSlotWidget.h"
#include "Widget/SupplyStoreWidget/SupplyStoreWidget.h"
#include "Structure/PlayerCharacterData/PlayerCharacterData.h"
#include "Component/PlayerCharacterMovementComponent/PlayerCharacterMovementComponent.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"
#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"

#include "Object/CameraShake/AttackCameraShake.h"
#include "Object/InteractionParam/SupplyNpcInteractParam/SupplyNpcInteractParam.h"

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

	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGETBP_CRITICALATTACK(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/CriticalAttackWidget/WidgetBP_CriticalAttack.WidgetBP_CriticalAttack_C'"));

	static ConstructorHelpers::FClassFinder<UPlayerStateSlotWidget> WIDGETBP_PLAYERSTATE(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/PlayerStateSlotWidget/WidgetBP_PlayerStateSlot.WidgetBP_PlayerStateSlot_C'"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGET_INTERACTION(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/InteractionWidget/WidgetBP_InteractionF.WidgetBP_InteractionF_C'"));

	static ConstructorHelpers::FClassFinder<USupplyStoreWidget> WIDGET_SUPPLYSTOREWIDGET(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/SkullyStoreWidget/WidgetBP_SupplyItem.WidgetBP_SupplyItem_C'"));


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

	if (WIDGETBP_CRITICALATTACK.Succeeded()) CriticalAttackWidget = WIDGETBP_CRITICALATTACK.Class;

	if (WIDGETBP_PLAYERSTATE.Succeeded()) PlayerStateSlotWidgetClass = WIDGETBP_PLAYERSTATE.Class;

	if (WIDGET_INTERACTION.Succeeded()) WidgetBP_InteractionKey = WIDGET_INTERACTION.Class;

	if (WIDGET_SUPPLYSTOREWIDGET.Succeeded()) SupplyStoreWidgetClass = WIDGET_SUPPLYSTOREWIDGET.Class;

	PlayerCharacterData = nullptr;

	// �÷��̾� ĳ���� ������ ����ϴ�.
	FString contextString;
	PlayerCharacterData = PlayerCharacterDataTable->FindRow<FPlayerCharacterData>(
		PLAYERCHARACTER_DATA_NORMAL, contextString);

	// Hp, Stamina �ʱ�ȭ
	CurrentHp = PlayerCharacterData->MaxHp;
	CurrentStamina = PlayerCharacterData->MaxStamina;

}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateStamina(DeltaTime);
	UpdateHp(DeltaTime);

	if (bIsActivateHpItem) RecoverHp(DeltaTime);

	CheckPlayerBuffState(DeltaTime);

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

	InputComponent->BindAction(TEXT("Interact_Item"), EInputEvent::IE_Pressed, this,
		&ThisClass::OnInteractItemInput);

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

	InputComponent->BindAction(TEXT("Next"), EInputEvent::IE_Pressed, this,
		&ThisClass::ProgressDialog);

	InputComponent->BindAction(TEXT("ConsumePortion"), EInputEvent::IE_Pressed, this,
		&ThisClass::ConsumeHpPortion);

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

	// WeaponStateWidget ���� / GameWidget �������̿� �߰�
	WeaponStateWidget = CreateWidget<UPlayerWeaponStateWidget>(this, WeaponStateWidgetClass);
	GameWidget->FloatingWidgetWeapon(WeaponStateWidget);

	CriticalWidget = CreateWidget<UUserWidget>(this, CriticalAttackWidget);
	CriticalWidget->SetVisibility(ESlateVisibility::Hidden);

	PlayerStateSlotWidget = CreateWidget<UPlayerStateSlotWidget>(this, PlayerStateSlotWidgetClass);

	// ���� ������ ���� ���� ����
	SupplyStoreWidget = CreateWidget<USupplyStoreWidget>(this, SupplyStoreWidgetClass);

	// ��ȣ�ۿ� ���� ����
	InteractionWidget = CreateWidget<UUserWidget>(this, WidgetBP_InteractionKey);

	// ������ ������ ȭ�鿡 ǥ���մϴ�.
	GameWidget->AddToViewport();

	// �÷��̾� ĳ���� ���� ���� �ʱ�ȭ
	InitializePlayerStateWidget(PlayerCharacterData->MaxHp, PlayerCharacterData->MaxStamina);

	// ���� ���� ���� �̹��� ���� �Լ� ���ε� 
	SetWeaponStateWidgetImage();
	
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

void AGamePlayerController::UpdateHp(float dt)
{
	UPlayerStateWidget* playerStateWidget = GameWidget->GetPlayerStateWidget();
	if (IsValid(playerStateWidget))
	{
		playerStateWidget->UpdateHp(CurrentHp);
	}
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

void AGamePlayerController::OnInteractItemInput()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	playerCharacter->OnInteractItemInput();
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



void AGamePlayerController::ProgressDialog()
{
	UE_LOG(LogTemp, Warning, TEXT("DialogNumber is %d"), DialogWidget->DialogNumber);
	++(DialogWidget->DialogNumber);
}

void AGamePlayerController::CheckPlayerBuffState(float deltaTime)
{
	if (SupplyInteractionItems.Num() == 0) return;

	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetPawn());
	if (!IsValid(gameCharacter)) return;

	for (USupplyNpcInteractParam* buff : SupplyInteractionItems)
	{
		if (buff->bIsEnable)
		{
			switch (buff->ItemType)
			{
			case ESupplyItemType::AtkBase:
			{
				// ���� ������� ���ݷ��� +15 ������ŵ�ϴ�.
				float atk = gameCharacter->GetAttackComponent()->GetCurrentAtk();
				gameCharacter->GetAttackComponent()->UpdateAtk(atk + 15.0f);
				SupplyInteractionItems.Remove(buff);
				UE_LOG(LogTemp, Warning, TEXT("Atk Buff is fire!"));
			}
			break;
			case ESupplyItemType::DefBase:
			{
				// ��� ������� ������ +10 ������ŵ�ϴ�.
				PlayerCharacterData->Def += 10.0f;
				SupplyInteractionItems.Remove(buff);
			}
			break;
			case ESupplyItemType::HpBase:
			{
				// ü�� ȸ�� ������� ü���� +30 ȸ���մϴ�.
				TargetHp = CurrentHp + 30.0f;

				bIsActivateHpItem = true;

				SupplyInteractionItems.Remove(buff);
			}
			break;
			case ESupplyItemType::CriticalBase:
			{
				// ġ��Ÿ Ȯ���� +20% ������ŵ�ϴ�.
				UE_LOG(LogTemp, Warning, TEXT("CriticalAttack"));
				SupplyInteractionItems.Remove(buff);
			}
			break;
			}
		}
	}
}

void AGamePlayerController::RecoverHp(float dt)
{
	CurrentHp = FMath::FInterpTo(CurrentHp, TargetHp, dt * 20.f, 1.0f);
	if (FMath::Abs(TargetHp - CurrentHp) == 0.0f) bIsActivateHpItem = false;
}

void AGamePlayerController::ConsumeHpPortion()
{
	// ���� ��� Ƚ���� 0 �̶�� �Լ� ȣ�� ����
	if (WeaponStateWidget->PortionCount == 0) return;

	// RecoverHp()�� ȣ�� �ϱ� ���� ���� ����
	TargetHp = CurrentHp + 30.0f;
	if (TargetHp > PlayerCharacterData->MaxHp) TargetHp = PlayerCharacterData->MaxHp;
	bIsActivateHpItem = true;

	// ���� ��� Ƚ�� ����
	WeaponStateWidget->ReducePortionCount();

	UE_LOG(LogTemp, Warning, TEXT("ConsumeHp"));

}

UGameWidget* AGamePlayerController::GetGameWidget() const
{
	return GameWidget;
}

UPlayerWeaponStateWidget* AGamePlayerController::GetWeaponStateWidget() const
{
	return WeaponStateWidget;
}

UPlayerStateSlotWidget* AGamePlayerController::GetPlayerStateSlotWidget() const
{
	return PlayerStateSlotWidget;
}

UUserWidget* AGamePlayerController::GetInteractionWidget() const
{
	return InteractionWidget;
}

USupplyStoreWidget* AGamePlayerController::GetSupplyStoreWidget() const
{
	return SupplyStoreWidget;
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
	PlayerDead();
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

void AGamePlayerController::ShowCriticalAttackWidget()
{
	CriticalWidget->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Warning, TEXT("ShowCriticalAttackWidget"));
}

void AGamePlayerController::PlayerDead()
{
	// Get PlayerCharacter
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());

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

		// �÷��̾� ��� �� �̵� ����
		playerCharacter->GetPlayerCharacterMovementComponent()->SetAllowMovementInput(false);

		// ��� �� ���� ���� ���� ǥ�� 
		GameWidget->ShowDeadWidget();
	}
}

void AGamePlayerController::SetWeaponStateWidgetImage()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetPawn());
	UPlayerEquipWeaponComponent* weaponComponent = playerCharacter->GetEquipWeaponComponent();

	FUpdateTextureEventSignature UpdateWeaponStateWidgetEvent;
	UpdateWeaponStateWidgetEvent.BindUObject(WeaponStateWidget, &UPlayerWeaponStateWidget::SetMainWeaponImage);
	weaponComponent->InitializeUpdateWeaponImageEvent(UpdateWeaponStateWidgetEvent);
}

void AGamePlayerController::AddSupplyItemCode(FName itemCode)
{
	LevelTransitionBuffCodes.Add(itemCode);
}




