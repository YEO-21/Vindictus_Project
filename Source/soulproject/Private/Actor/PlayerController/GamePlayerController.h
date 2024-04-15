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

	// ���� ����
	UPROPERTY()
	class UGameWidget * GameWidget;

	// �÷��̾� ĳ���� ������
	struct FPlayerCharacterData* PlayerCharacterData;

	// ���� Hp
	float CurrentHp;

	// ���� Stamina
	float CurrentStamina;

	// ���¹̳ʸ� ����ϱ� ���� ���� ĳ���� ��ġ
	FVector PrevCharacterLocation;



public :
	AGamePlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected :
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* pawn) override;

private :
	void UpdateStamina(float dt);

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


		
public :
	class UGameWidget* GetGameWidget() const;

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

	
};
