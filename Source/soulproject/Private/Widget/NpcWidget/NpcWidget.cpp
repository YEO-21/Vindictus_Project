#include "Widget/NpcWidget/NpcWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/Actor.h"

void UNpcWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
}

void UNpcWidget::InitializeNpcWidget(AActor* ownerCharacter, AActor* gameCharacter, FText npcName)
{
	OwnerCharacter = ownerCharacter;
	GameCharacter = gameCharacter;
	Text_Name->SetText(npcName);
	UE_LOG(LogTemp, Warning, TEXT("npcName = %s"), *npcName.ToString());
}

void UNpcWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// ���̵��� ���۵Ǵ� �Ÿ�
	float fadeStartDistance = 300.0f;

	// ������ �������� �Ÿ�
	float fadedDistance = 500.0f;

	// �÷��̾�� NPC ������ �Ÿ�
	float distance = FVector::Distance(OwnerCharacter->GetActorLocation(), GameCharacter->GetActorLocation());


	FLinearColor color = Text_Name->GetColorAndOpacity().GetSpecifiedColor();

	float Alpha = 1.0f;
	if (distance < fadeStartDistance)
		Alpha = 1.0f;
	else if (distance > fadedDistance)
		Alpha = 0.0f;
	else Alpha = 1.0f - ((distance - fadeStartDistance) / (fadedDistance - fadeStartDistance));

	color.A = Alpha;

	Text_Name->SetColorAndOpacity(color);
}
