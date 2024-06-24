#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragonCharacterAttackComponent.generated.h"


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
	void CheckAttackArea();
		
};
