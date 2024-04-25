// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class UGameWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class UOverlay * Overlay_Player;

	UPROPERTY()
	class UOverlay * Overlay_Additive;

	UPROPERTY()
	class UTextBlock* TextBlock_Dead;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* TextBlock_Dead_Animation;

	// 상태 위젯을 나타냅니다.
	UPROPERTY()
	class UPlayerStateWidget * PlayerStateWidget;

	// 적 상태 위젯을 나타냅니다.
	UPROPERTY()
	class UEnemyStateWidget* EnemyStateWidget;

	// 적 상태 위젯이 띄워진 시간을 저장할 변수
	UPROPERTY()
	float EnemyStateWidgetFloatingTime;


protected : 
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& myGeometry, float dt) override;

public :
	// Overlay_Additive 에 위젯을 추가합니다.
	void FloatingWidgetAdditive(class UUserWidget* widgetInstance);

	// Overlay_Additive 에 추가된 위젯을 제거합니다.
	void RemoveWidgetAdditive(class UUserWidget* widgetForClose);

	// 상태 위젯을 반환합니다.
	class UPlayerStateWidget* GetPlayerStateWidget() const;

	void ShowEnemyState(class AEnemyCharacter* newTargetEnemy);
	void HideEnemyState();
	
	void ShowDeadWidget();
	void HideDeadWidget();
};
