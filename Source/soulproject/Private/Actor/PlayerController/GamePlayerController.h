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
	// 플레이어 데이터 테이블 에셋
	UPROPERTY()
	class UDataTable* PlayerCharacterDataTable;

	// 게임 위젯 블루프린트 클래스
	UPROPERTY()
	TSubclassOf<class UGameWidget> GameWidgetClass;

	// 게임 위젯
	UPROPERTY()
	class UGameWidget * GameWidget;

	// 플레이어 캐릭터 데이터
	struct FPlayerCharacterData* PlayerCharacterData;

	// 현재 Hp
	float CurrentHp;

	// 현재 Stamina
	float CurrentStamina;

	// 스태미너를 계산하기 위한 이전 캐릭터 위치
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
	// 수직 축 입력 시 호출됩니다.
	void OnVerticalMovementInput(float axis);

	// 수평 축 입력 시 호출됩니다.
	void OnHorizontalMovementInput(float axis);

	// 마우스 수평 축 입력 시 호출됩니다.
	void OnMouseXInput(float axis);

	// 마우스 수직 축 입력 시 호출됩니다.
	void OnMouseYInput(float axis);

	// 마우스 휠 입력 시 호출됩니다.
	void OnZoomInput(float axis);

	// 점프 입력 시 호출됩니다.
	void OnJumpInput();

	// 공격 입력 시 호출됩니다.
	void OnAttackInput();

	// 상호작용 키 입력 시 호출됩니다.
	void OnInteractInput();

	void OnRollForward();
	void OnRollBackward();
	void OnRollRight();
	void OnRollLeft();

	// 방어 키 눌림 / 떼어짐 함수
	void OnBlockPressed();
	void OnBlockReleased();

	// 달리기 키 눌림 / 떼어짐 함수
	void OnRunPressed();
	void OnRunReleased();

	// 무기 교체 입력 시 호출됩니다.
	void OnWeaponChangePressed();


		
public :
	class UGameWidget* GetGameWidget() const;

	void SetCameraViewTarget(class AActor* target);
	void ClearCameraViewTarget();

	// 상태 위젯을 초기화합니다.
	void InitializePlayerStateWidget(float maxHp, float maxStamina);

	// 조종하는 캐릭터가 피해를 입을 경우 호출됩니다.
	// damage : 입은 피해량이 전달됩니다.
	void OnDamaged(float damage);

	// 적 공격 시 호출됩니다.
	// newTargetEnemy : 공격한 적 객체를 전달합니다.
	void OnEnemyAttack(class AEnemyCharacter * newTargetEnemy);

	
};
