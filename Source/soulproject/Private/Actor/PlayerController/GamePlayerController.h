// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

#define PLAYERCHARACTER_DATA_NORMAL		TEXT("Normal")


/**
 * 
 */
UCLASS()
class AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

private :
	// �÷��̾� ������ ���̺� ����
	UPROPERTY()
	class UDataTable* PlayerCharacterDataTable;

	// ���� ���� �������Ʈ Ŭ����
	UPROPERTY()
	TSubclassOf<class UGameWidget> GameWidgetClass;

	UPROPERTY()
	TSubclassOf<class UPlayerWeaponStateWidget> WeaponStateWidgetClass;

	// ���� ����
	UPROPERTY()
	class UGameWidget * GameWidget;

	// ������� ����
	UPROPERTY()
	class UPlayerWeaponStateWidget* WeaponStateWidget;

	// ��ȭ ����
	UPROPERTY()
	class UNpcDialogWidget* DialogWidget;


	// �÷��̾� ���� ���� �������Ʈ Ŭ����
	UPROPERTY()
	TSubclassOf<class UPlayerStateSlotWidget> PlayerStateSlotWidgetClass;


	// �÷��̾� ���� ����
	UPROPERTY()
	class UPlayerStateSlotWidget* PlayerStateSlotWidget;


	// ũ��Ƽ�� ���� ���� Ŭ����
	UPROPERTY()
	TSubclassOf<class UUserWidget> CriticalAttackWidget;

	// ũ��Ƽ�� ���� ����
	UPROPERTY()
	class UUserWidget* CriticalWidget;

	UPROPERTY()
	TSubclassOf<class UNpcDialogWidget> DialogWidgetClass;

	// ��ȣ�ۿ� ���� Ŭ����
	UPROPERTY()
	TSubclassOf<UUserWidget> WidgetBP_InteractionKey;

	// ��ȣ�ۿ� ����
	UPROPERTY()
	UUserWidget* InteractionWidget;

	


	// �÷��̾� ĳ���� ������
	struct FPlayerCharacterData* PlayerCharacterData;

	// ���� Hp
	float CurrentHp;

	// ��ǥ Hp
	float TargetHp;

	// ���� Stamina
	float CurrentStamina;

	// ���� ����
	float CurrentDef;

	// Hp ���� �Լ��� �����Ű�� ���� �����Դϴ�.
	bool bIsActivateHpItem;


	// ���¹̳ʸ� ����ϱ� ���� ���� ĳ���� ��ġ
	FVector PrevCharacterLocation;

protected:
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class USupplyNpcInteractParam*> SupplyInteractionItems;


public :
	AGamePlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected :
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* pawn) override;

private :
	void UpdateStamina(float dt);
	void UpdateHp(float dt);

private :
	// ���� �� �Է� �� ȣ��˴ϴ�.
	void OnVerticalMovementInput(float axis);

	// ���� �� �Է� �� ȣ��˴ϴ�.
	void OnHorizontalMovementInput(float axis);

	// ���콺 ���� �� �Է� �� ȣ��˴ϴ�.
	void OnMouseXInput(float axis);

	// ���콺 ���� �� �Է� �� ȣ��˴ϴ�.
	void OnMouseYInput(float axis);

	// ���콺 �� �Է� �� ȣ��˴ϴ�.
	void OnZoomInput(float axis);

	// ���� �Է� �� ȣ��˴ϴ�.
	void OnJumpInput();

	// ���� �Է� �� ȣ��˴ϴ�.
	void OnAttackInput();

	// ��ȣ�ۿ� Ű �Է� �� ȣ��˴ϴ�.
	void OnInteractInput();

	void OnInteractItemInput();

	void OnRollForward();
	void OnRollBackward();
	void OnRollRight();
	void OnRollLeft();

	// ��� Ű ���� / ������ �Լ�
	void OnBlockPressed();
	void OnBlockReleased();

	// �޸��� Ű ���� / ������ �Լ�
	void OnRunPressed();
	void OnRunReleased();

	// ���� ��ü �Է� �� ȣ��˴ϴ�.
	void OnWeaponChangePressed();

	// ��ȭ ���� �� ȣ��˴ϴ�.
	void ProgressDialog();

	// �÷��̾��� ���� ���¸� Ȯ���մϴ�.
	void CheckPlayerBuffState(float deltaTime);

	// �÷��̾� HP�� ȸ����Ű�� �Լ�
	void RecoverHp(float dt);


		
public :
	class UGameWidget* GetGameWidget() const;
	class UPlayerWeaponStateWidget* GetWeaponStateWidget() const;
	class UPlayerStateSlotWidget* GetPlayerStateSlotWidget() const;
	class UUserWidget* GetInteractionWidget() const;


	void SetCameraViewTarget(class AActor* target);
	void ClearCameraViewTarget();

	// ���� ������ �ʱ�ȭ�մϴ�.
	void InitializePlayerStateWidget(float maxHp, float maxStamina);

	// �����ϴ� ĳ���Ͱ� ���ظ� ���� ��� ȣ��˴ϴ�.
	// damage : ���� ���ط��� ���޵˴ϴ�.
	void OnDamaged(float damage);

	// �� ���� �� ȣ��˴ϴ�.
	// newTargetEnemy : ������ �� ��ü�� �����մϴ�.
	void OnEnemyAttack(class AEnemyCharacter * newTargetEnemy);

	void ResetPlayerCharacterWidget();

	void ShowCriticalAttackWidget();

	// �÷��̾��� ��� ó���� �մϴ�.
	void PlayerDead();


	FORCEINLINE float GetCurrentHp()
	{
		return CurrentHp;
	}

	FORCEINLINE float GetCurrentStamina()
	{
		return CurrentStamina;
	}

	void SetCurrentHp(float hp)
	{
		CurrentHp = hp;
	}

	void SetCurrentStamina(float stamina)
	{
		CurrentStamina = stamina;
	}

	
};
