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
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInAnimation;


	UPROPERTY()
	class UTextBlock* Text_Name;

	UPROPERTY()
	class UTextBlock* Text_Dialog;

	UPROPERTY()
	class UButton* Button_Close;



protected:
	virtual void NativeConstruct() override;

public :
	void InitializeNpcDialogWidget(struct FNpcData* npcData, FOnDialogCloseEventSignature onDialogClosed);

private :
	UFUNCTION()
	void OnCloseButtonClicked();

	
};
