// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupplyStoreWidget.generated.h"

DECLARE_EVENT(USupplyStoreWidget, SupplyItemBuyButtonClickSignature)

UCLASS()
class USupplyStoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// 지원 아이템 구매 버튼
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_SupplyItem;

	// 지원 아이템 이미지
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_SupplyItem;

	// 지원 아이템 설명 텍스트
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_SupplyItem;

	// 지원 아이템 정보를 담은 데이터테이블 에셋입니다.
	class UDataTable* DT_SupplyItemData;

	// 지원 아이템 코드
	UPROPERTY()
	FName SupplyItemCode;

	SupplyItemBuyButtonClickSignature SupplyItemBuyEvent;

public:
	// 지원 아이템 정보를 나타냅니다.
	struct FSupplyItemData* PlayerSupplyData;


public:
	USupplyStoreWidget(const FObjectInitializer& ObjectInitializer);

	void SetSupplyItemCode(FName itemCode);

	void SetImageMaterial(UMaterialInterface* material);

	void SetText(FText text);

	void InitializeSupplyStoreWidget();

	void InitializeItemCode(FName itemCode);

	void InitializeSupplyItem(SupplyItemBuyButtonClickSignature supplyEvent);

protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
	void OnBuyButtonClicked();
	
};
