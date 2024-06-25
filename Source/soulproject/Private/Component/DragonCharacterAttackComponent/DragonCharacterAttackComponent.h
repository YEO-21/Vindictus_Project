#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragonCharacterAttackComponent.generated.h"

// 왼쪽 공격 소켓 이름
#define DRAGON_ATTACK_LEFTLEG_SOCKET_START			TEXT("Socekt_LFLegAttackStart")
#define DRAGON_ATTACK_LEFTLEG_SOCKET_END			TEXT("Socket_LFLeg")

// 오른쪽 공격 소켓 이름
#define DRAGON_ATTACK_RIGHTLEG_SOCKET_START			TEXT("Socket_RFLegAttackStart")
#define DRAGON_ATTACK_RIGHTLEG_SOCKET_END			TEXT("Socket_RFLeg")



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDragonCharacterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	UPROPERTY()
	bool IsBreathFire;

	UPROPERTY()
	bool IsClawAttack;

	UPROPERTY()
	bool IsRushAttack;
	
	// 드래곤의 공격 영역 체크 활성화 여부
	UPROPERTY()
	bool bIsAttackCheckEnabled;

	UPROPERTY()
	class UAnimMontage* ParriedAnimMontage;

	// 피해를 입힌 액터를 임시로 저장할 배열
	TArray<class AActor*> TempDamagedActors;



public:	
	UDragonCharacterAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void StartBreathFire();
	void OnBreathFireFinished();

	void StartClawAttack();
	void FinishClawAttack();

	void StartRushAttack();
	void FinishRushAttack();

	// 공격 영역 활성화
	void EnableAttackArea();

	// 공격 영역 비활성화
	void DisableAttackArea();

public:
	FORCEINLINE bool GetBreathFireState() const
	{
		return IsBreathFire;
	}

	FORCEINLINE bool GetClawAttackState() const
	{
		return IsClawAttack;
	}
	
	FORCEINLINE bool GetRushAttackState() const
	{
		return IsRushAttack;
	}

private:
	// 공격 영역을 검사합니다.
	void CheckAttackArea();

	// 방어 처리되었음을 반환합니다.
	bool IsBlocked(class AGameCharacter* gameCharacter, class AActor* ownerEnemy) const;
		
};
