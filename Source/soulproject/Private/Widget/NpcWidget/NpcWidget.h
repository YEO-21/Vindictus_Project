#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNpcWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class UTextBlock* Text_Name;

	UPROPERTY()
	class AActor* OwnerCharacter;

	UPROPERTY()
	class AActor * GameCharacter;

public :
	virtual void NativeConstruct() override;

	void InitializeNpcWidget(class AActor* ownerCharacter, class AActor* gameCharacter, FText npcName);

protected : 
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
	
};
