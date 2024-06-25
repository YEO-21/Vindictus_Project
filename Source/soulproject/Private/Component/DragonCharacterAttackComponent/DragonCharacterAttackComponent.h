#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragonCharacterAttackComponent.generated.h"

// ���� ���� ���� �̸�
#define DRAGON_ATTACK_LEFTLEG_SOCKET_START			TEXT("Socekt_LFLegAttackStart")
#define DRAGON_ATTACK_LEFTLEG_SOCKET_END			TEXT("Socket_LFLeg")

// ������ ���� ���� �̸�
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
	
	// �巡���� ���� ���� üũ Ȱ��ȭ ����
	UPROPERTY()
	bool bIsAttackCheckEnabled;

	UPROPERTY()
	class UAnimMontage* ParriedAnimMontage;

	// ���ظ� ���� ���͸� �ӽ÷� ������ �迭
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

	// ���� ���� Ȱ��ȭ
	void EnableAttackArea();

	// ���� ���� ��Ȱ��ȭ
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
	// ���� ������ �˻��մϴ�.
	void CheckAttackArea();

	// ��� ó���Ǿ����� ��ȯ�մϴ�.
	bool IsBlocked(class AGameCharacter* gameCharacter, class AActor* ownerEnemy) const;
		
};
