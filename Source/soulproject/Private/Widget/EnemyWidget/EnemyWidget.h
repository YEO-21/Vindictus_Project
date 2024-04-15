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
	// 적 위젯을 초기화합니다.
	// name : 적 이름을 전달합니다.
	// maxHp : 적의 최대 체력을 전달합니다.
	void InitializeEnemyWidget(FText name, float maxHp);

	// Hp을 설정합니다.
	void SetHp(float newHp);

	
	void ShowWidget();

	UFUNCTION()
	void HideWidget();
	
};
