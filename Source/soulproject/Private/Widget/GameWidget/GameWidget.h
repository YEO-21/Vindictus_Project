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
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay_All;

	UPROPERTY()
	class UOverlay * Overlay_Player;

	UPROPERTY()
	class UOverlay * Overlay_Additive;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay_Weapon;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay_PlayerState;
	

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
	
	// 크리티컬 공격을 나타내는 위젯입니다.
	UPROPERTY()
	class UUserWidget* CriticalAttackWidget;

protected:
	// 플레이어 상태 슬롯 위젯을 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerStateSlotWidget* PlayerStateSlotWidget;


protected : 
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& myGeometry, float dt) override;

public :
	// Overlay_Additive 에 위젯을 추가합니다.
	void FloatingWidgetAdditive(class UUserWidget* widgetInstance);

	// Overlay_Additive 에 추가된 위젯을 제거합니다.
	void RemoveWidgetAdditive(class UUserWidget* widgetForClose);

	// Overlay_PlayerState 에 위젯을 추가합니다.
	void FloatingWidgetPlayerState(class UUserWidget* widgetInstance);



	// 상태 위젯을 반환합니다.
	class UPlayerStateWidget* GetPlayerStateWidget() const;

	void ShowEnemyState(class AEnemyCharacter* newTargetEnemy);
	void HideEnemyState();
	
	void ShowDeadWidget();
	void HideDeadWidget();

	void ShowWeaponWidget();
	void HideWeaponWidget();

	void ShowCriticalWidget();
	void HideCriticalWidget();

	void ShowPlayerStateWidget();
	void HidePlayerStateWidget();

	UFUNCTION(BlueprintCallable)
	void HideAllWidget();

	UFUNCTION(BlueprintCallable)
	void ShowAllWidget();

	void InitializePlayerStateSlotWidget(UPlayerStateSlotWidget* playerSlotWidget);
};
