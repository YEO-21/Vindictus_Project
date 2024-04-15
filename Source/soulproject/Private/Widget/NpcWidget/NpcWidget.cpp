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

	// 페이딩이 시작되는 거리
	float fadeStartDistance = 300.0f;

	// 완전히 숨겨지는 거리
	float fadedDistance = 500.0f;

	// 플레이어와 NPC 사이의 거리
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
