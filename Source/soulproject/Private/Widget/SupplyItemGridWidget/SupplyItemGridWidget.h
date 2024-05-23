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
	// 균등 그리드 패널을 나타냅니다.
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGridPanel;

	// 지원 아이템 위젯 클래스를 나타냅니다.
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
