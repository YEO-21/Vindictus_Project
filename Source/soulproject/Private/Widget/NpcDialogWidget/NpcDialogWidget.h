// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcDialogWidget.generated.h"

DECLARE_EVENT(UNpcDialogWidget, FOnDialogCloseEventSignature)


/**
 * 
 */
UCLASS()
class UNpcDialogWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	FOnDialogCloseEventSignature OnDialogClosed;


protected :
	UPROPERTY()
	class UOverlay* Overlay_Parent;

	UPROPERTY()
	class UInteractionParamBase* UIInteractionParam;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInAnimation;


	UPROPERTY()
	class UTextBlock* Text_Name;

	UPROPERTY()
	class UTextBlock* Text_Dialog;

	UPROPERTY()
	class UButton* Button_Close;

public:
	UPROPERTY()
	int32 DialogNumber;

	



protected:
	virtual void NativeConstruct() override;



public :
	void InitializeNpcDialogWidget(struct FNpcData* npcData, FOnDialogCloseEventSignature onDialogClosed, class UInteractionParamBase* interactionParam);

	class UInteractionParamBase* GetInteractionParam();

private :
	UFUNCTION()
	void OnCloseButtonClicked();

protected:
	void HideDialogWidget();

	
};
