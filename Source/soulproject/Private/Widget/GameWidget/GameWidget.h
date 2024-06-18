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

	// ���� ������ ��Ÿ���ϴ�.
	UPROPERTY()
	class UPlayerStateWidget * PlayerStateWidget;


	// �� ���� ������ ��Ÿ���ϴ�.
	UPROPERTY()
	class UEnemyStateWidget* EnemyStateWidget;

	// �� ���� ������ ����� �ð��� ������ ����
	UPROPERTY()
	float EnemyStateWidgetFloatingTime;
	
	// ũ��Ƽ�� ������ ��Ÿ���� �����Դϴ�.
	UPROPERTY()
	class UUserWidget* CriticalAttackWidget;

protected:
	// �÷��̾� ���� ���� ������ ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerStateSlotWidget* PlayerStateSlotWidget;


protected : 
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& myGeometry, float dt) override;

public :
	// Overlay_Additive �� ������ �߰��մϴ�.
	void FloatingWidgetAdditive(class UUserWidget* widgetInstance);

	// Overlay_Additive �� �߰��� ������ �����մϴ�.
	void RemoveWidgetAdditive(class UUserWidget* widgetForClose);

	// Overlay_PlayerState �� ������ �߰��մϴ�.
	void FloatingWidgetPlayerState(class UUserWidget* widgetInstance);



	// ���� ������ ��ȯ�մϴ�.
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
