// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupplyStoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class USupplyStoreWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// ���� ������ ���� ��ư
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_SupplyItem;

	// ���� ������ �̹���
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_SupplyItem;

	// ���� ������ ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_SupplyItem;

	// ���� ������ ������ ���� ���������̺� �����Դϴ�.
	class UDataTable* DT_SupplyItemData;

	// ���� ������ �ڵ�
	UPROPERTY()
	FName SupplyItemCode;

public:
	// ���� ������ ������ ��Ÿ���ϴ�.
	struct FSupplyItemData* PlayerSupplyData;


public:
	USupplyStoreWidget(const FObjectInitializer& ObjectInitializer);

	void SetSupplyItemCode(FName itemCode);

	void SetImageMaterial(UMaterialInterface* material);

	void InitializeSupplyStoreWidget();

	void InitializeItemCode(FName itemCode);

protected:
	virtual void NativeConstruct() override;


	
};
