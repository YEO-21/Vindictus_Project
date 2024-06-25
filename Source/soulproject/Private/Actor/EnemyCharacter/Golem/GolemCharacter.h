#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "GolemCharacter.generated.h"

UCLASS()
class AGolemCharacter : public AEnemyCharacter
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* GolemMovingWheel;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* GolemHead;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* GolemAggressiveArea;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UGolemAttackComponent* GolemAttackComponent;

	UPROPERTY()
	class UAnimMontage* HitGolemAnim;




public:
	AGolemCharacter();


protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage) override;


	virtual void BeginPlay() override;

public:
	virtual void Tick(float dt) override;

	FORCEINLINE class UGolemAttackComponent* GetGolemAttackComponent()
	{
		return GolemAttackComponent;
	}


// 골렘 공격 영역 오버랩 시 호출될 함수들입니다.
private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);


	


};
