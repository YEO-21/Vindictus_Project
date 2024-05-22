#include "Widget/NpcDialogWidget/SkullyItemWidget/SkullyItemWidget.h"

#include "Actor/GameCharacter/GameCharacter.h"

#include "Object/InteractionParam/ComsumeNpcInteractParam/ComsumeNpcInteractParam.h"

void USkullyItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FTimerDelegate timerDelegate;
	timerDelegate.BindUObject(this, &ThisClass::CreateWeaponWidget);

	GetOwningPlayer()->GetWorldTimerManager().SetTimer(SkullyItemShowTimerHandle,
		timerDelegate, 3.0f, false);

}

void USkullyItemWidget::CreateWeaponWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateWeaponWidget"));

	UComsumeNpcInteractParam* interactionParam = Cast<UComsumeNpcInteractParam>(UIInteractionParam);
	USkullyItemWidget* weaponStoreWidget = CreateWidget<USkullyItemWidget>(this, interactionParam->BP_SkullyItemWidgetClass);

	AGameCharacter* gameCharacter =
		Cast<AGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());


}
