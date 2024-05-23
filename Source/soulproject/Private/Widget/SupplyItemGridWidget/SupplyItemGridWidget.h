// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupplyItemGridWidget.generated.h"

/**
 * 
 */

#define MAX_ROW				2
#define MAX_COLUMN			2

#define ATK					TEXT("000001")
#define DEF					TEXT("000002")
#define HP					TEXT("000003")
#define CRITICAL			TEXT("000004")

UCLASS()
class USupplyItemGridWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// �յ� �׸��� �г��� ��Ÿ���ϴ�.
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGridPanel;

	// ���� ������ ���� Ŭ������ ��Ÿ���ϴ�.
	TSubclassOf<class USupplyStoreWidget> WidgetBP_SkullyStore;

	UPROPERTY()
	TArray<FName> itemCodes;



public:
	USupplyItemGridWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	
public:
	void InitializeSupplyStoreWidget();

};
