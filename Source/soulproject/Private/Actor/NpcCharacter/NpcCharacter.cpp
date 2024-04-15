#include "Actor/NpcCharacter/NpcCharacter.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Structure/NpcData/NpcData.h"

#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

#include "Component/InteractableAreaComponent/InteractableAreaComponent.h"

#include "Widget/GameWidget/GameWidget.h"
#include "Widget/NpcWidget/NpcWidget.h"
#include "Widget/NpcDialogWidget/NpcDialogWidget.h"

#include "Kismet/GameplayStatics.h"



ANpcCharacter::ANpcCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_NPCDATA(
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_NpcData.DT_NpcData'"));
	if (DT_NPCDATA.Succeeded())
	{
		DT_NpcData = DT_NPCDATA.Object;
	}

	static ConstructorHelpers::FClassFinder<UNpcWidget> WIDGETBP_NPC(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/NpcWidget/WidgetBP_Npc.WidgetBP_Npc_C'"));

	// ��ȣ�ۿ� �� Ÿ�� ī�޶� ������Ʈ
	InteractionViewTargetCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VIEWTARGET_CAM_COMP"));
	InteractionViewTargetCamera->SetupAttachment(GetRootComponent());

	// ��ȣ�ۿ� �� �÷��̾� ĳ���Ͱ� ��ġ�� ��ġ
	InteractionLocation = CreateDefaultSubobject<USceneComponent>(TEXT("INTERACTION_LOCATION"));
	InteractionLocation->SetupAttachment(GetRootComponent());

	// ��ȣ�ۿ� ������ ���� ������Ʈ
	InteractableAreaComponent =
		CreateDefaultSubobject<UInteractableAreaComponent>(TEXT("INTERACTABLE_AREA_COMPONENT"));
	InteractableAreaComponent->SetupAttachment(GetRootComponent());
	InteractableAreaComponent->SetSphereRadius(300.0f);

	// ���� ������Ʈ ����
	NpcWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGET_COMP"));
	NpcWidgetComponent->SetupAttachment(GetRootComponent());
	NpcWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NpcWidgetComponent->SetRelativeLocation(
		FVector::UpVector * GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	if (WIDGETBP_NPC.Succeeded())
	{
		NpcWidgetComponent->SetWidgetClass(WIDGETBP_NPC.Class);
	}


	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeNpcData();

	// NPC ���� �ʱ�ȭ
	UNpcWidget* npcWidget = Cast<UNpcWidget>(NpcWidgetComponent->GetUserWidgetObject());

	// �÷��̾� ĳ���� ����
	AActor* gameCharacter = UGameplayStatics::GetActorOfClass(GetWorld(), AGameCharacter::StaticClass());
	npcWidget->InitializeNpcWidget(this, gameCharacter, NpcData->Name);
}

void ANpcCharacter::InitializeNpcData()
{
	if (NpcCode.IsNone())
	{
		NpcData = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("NpcCode is none"));
		return;
	}

	FString contextString;
	NpcData = DT_NpcData->FindRow<FNpcData>(NpcCode, contextString);
}

void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ANpcCharacter::OnInteractionStarted(FOnInteractionFinishEventSignature onInteractionFinished)
{
	// ù ��° �÷��̾� ��Ʈ�ѷ� (�÷��̾��� ��Ʈ�ѷ�)�� ����ϴ�.
	AGamePlayerController* playerController = Cast<AGamePlayerController>(
		GetWorld()->GetFirstPlayerController());

	if (!IsValid(NpcData->DialogWidetClass))
		return false;

	OnInteractionFinished = onInteractionFinished;


	// ǥ���� ������ �����մϴ�.
	NpcDialogWidget = CreateWidget<UNpcDialogWidget>(playerController, NpcData->DialogWidetClass);

	// Npc Dialog ������ ���ϴ�.
	UGameWidget* gameWidget = playerController->GetGameWidget();
	gameWidget->FloatingWidgetAdditive(NpcDialogWidget);

	// ���� �ʱ�ȭ
	FOnDialogCloseEventSignature onDialogClosed;
	onDialogClosed.AddLambda([gameWidget, playerController, this]() {
			// ���� ����
			gameWidget->RemoveWidgetAdditive(NpcDialogWidget); 

			// �Է� ��带 Game ���� ��ȯ�մϴ�.
			playerController->SetInputMode(FInputModeGameOnly());

			// Ŀ���� ����ϴ�.
			playerController->bShowMouseCursor = false;

			// ��ȣ�ۿ� ����
			if (OnInteractionFinished.IsBound()) 
				OnInteractionFinished.Broadcast();
		});

	NpcDialogWidget->InitializeNpcDialogWidget(NpcData, onDialogClosed);

	// �Է� ��带 UI ���� ��ȯ�մϴ�.
	playerController->SetInputMode(FInputModeUIOnly());

	// Ŀ���� ǥ���մϴ�.
	playerController->bShowMouseCursor = true;

	return true;
}

FVector ANpcCharacter::GetInteractionLocation() const
{
	return InteractionLocation->GetComponentLocation();
}

FRotator ANpcCharacter::GetInteractionRotation() const
{
	return InteractionLocation->GetComponentRotation();
}
