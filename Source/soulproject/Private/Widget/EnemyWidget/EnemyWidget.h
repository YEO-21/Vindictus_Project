// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	float MaxHp;

protected :
	UPROPERTY()
	class UTextBlock * Text_Name;

	UPROPERTY()
	class UProgressBar * Progressbar_Hp;

protected :
	virtual void NativeConstruct() override;

public :
	// �� ������ �ʱ�ȭ�մϴ�.
	// name : �� �̸��� �����մϴ�.
	// maxHp : ���� �ִ� ü���� �����մϴ�.
	void InitializeEnemyWidget(FText name, float maxHp);

	// Hp�� �����մϴ�.
	void SetHp(float newHp);

	
	void ShowWidget();

	UFUNCTION()
	void HideWidget();
	
};
