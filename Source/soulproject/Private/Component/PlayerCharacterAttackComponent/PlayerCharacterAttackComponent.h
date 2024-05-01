// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterAttackComponent.generated.h"

// 아무 공격도 하고있지 않음을 나타낼 매크로 상수
#define ATTACK_NONE				TEXT("NONE")

// 기본 공격을 나타내는 키워드
#define DEFAULT_ATTACK_KEYWORD	TEXT("DefaultAttack")

// 무기 Static Mesh 소켓 이름
#define WEAPON_SOCKET_START		TEXT("Socket_SaberStart")
#define WEAPON_SOCKET_END		TEXT("Socket_SaberEnd")




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	// 공격 데이터 테이블을 나타냅니다.
	class UDataTable* DT_AttackData;

	// 바로 이전에 실행시킨 공격 정보를 나타냅니다.
	struct FAttackData* PrevAttackData;

	// 현재 실행중인 공격을 나타냅니다.
	struct FAttackData* CurrentAttackData;

	// 현재 캐릭터에게 적용된 공격력
	float Atk;

	// 현재 공격이 적중한 경우 가할 대미지
	float ApplyDamage;

	// 공격 영역 활성화 상태를 나타냅니다.
	bool IsAttackAreaEnabled;

	// 방어 입력을 시작한 시간을 나타냅니다.
	float BlockStartTime;

	// 공격 시 감지된 적 객체를 잠시 저장해둘 배열
	TArray<class AEnemyCharacter*> AttackDetectedEnemies;

	// 공격 시 감지된 액터들을 잠시 저장해둘 배열
	TArray<class AActor*> AttackDetectedActors;



	// 입력된 콤보 카운트
	int32 TargetCombo;

	// 현재까지 진행된 콤보 카운트를 나타냅니다.
	int32 CurrentCombo;

	// 다음 공격 입력을 확인하고 있음을 나타냅니다.
	bool bCheckingNextAttackInput;

	// 요청된 공격 큐
	TQueue<struct FAttackData*> RequestAttackQueue;

	// 플레이어 캐릭터 객체를 나타냅니다.
	class AGameCharacter* PlayerCharacter;

	// 현재 공격중임을 나타냅니다.
	bool IsAttacking;

	// 현재 방어중임을 나타냅니다.
	bool IsBlocking;

	// 무기의 현재 위치를 나타냅니다.
	FVector CurrentSaberStartSocketLocation;
	FVector CurrentSaberEndSocketLocation;

	// 공격 모션 코드
	FName AttackCode;




public:	
	UPlayerCharacterAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// 스킬을 순서대로 처리합니다.
	void AttackProcedure();

	// 공격 영역을 확인합니다.
	void CheckAttackArea();

	// 창 무기로 공격을 하는지 확인합니다.
	void CheckSpearAttack();

public :
	void UpdateAtk(float atk);

	// 무기 소켓 위치를 갱신합니다.
	// weaponMesh : 소켓 위치를 얻을 StaticMesh 에셋을 전달합니다.
	void UpdateWeaponSocketLocation(class UStaticMeshComponent* weaponMesh);

	// 현재 공격을 비웁니다.
	void ClearCurrentAttack();

	// 공격 상태를 취소합니다.
	void CancelAttackState();

	// 공격을 요청합니다.
	void RequestAttack(FName attackName);

	// 다음 공격 입력 확인 시작
	void StartCheckingNextAttackInput();

	// 다음 공격 입력 확인 끝
	void FinishCheckingNextAttackInput();

	// 공격 영역 활성화
	void EnableAttackArea();

	// 공격 영역 비활성화
	void DisableAttackArea();

	// 방어 시작
	void OnBlockStarted();

	// 방어 끝
	void OnBlockFinished();

	FAttackData* GetAttackData();

	FORCEINLINE bool GetAttackState() const
	{
		return IsAttacking;
	}

	FORCEINLINE bool GetBlockState() const
	{
		return IsBlocking;
	}

	FORCEINLINE float GetBlockStartTime() const
	{
		return BlockStartTime;
	}


};
