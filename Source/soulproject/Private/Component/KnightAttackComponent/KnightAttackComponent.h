#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnightAttackComponent.generated.h"


#define SWORD_SOCKET_START	TEXT("Socket_Start")
#define SWORD_SOCKET_END	TEXT("Socket_End")

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UKnightAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	struct FEnemyData* EnemyData;

	UPROPERTY()
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY()
	class UAnimMontage* ParriedAnimMontage;


	// 공격 위치를 찾기 위한 Sword MeshComponent
	UPROPERTY()
	class UStaticMeshComponent * SwordMeshComponent;

	// 공격 영역 활성화 여부
	UPROPERTY()
	bool IsAttackAreaEnabled;

	// 피해를 입힌 액터를 임시로 저장할 배열
	TArray<class AActor*> TempDamagedActors;

public:	
	UKnightAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 방어 처리되었음을 반환합니다.
	bool IsBlocked(class AGameCharacter* gameCharacter, class AActor* ownerEnemy) const;

	// 공격 영역 검사
	void CheckAttackArea();



public:
	void InitializeAttackComponent(class UStaticMeshComponent* swordMeshComponent, 
		struct FEnemyData* enemyData);

	void Attack();
	void OnAttackFinished();

	// 공격 영역 활성화
	void EnableAttackArea();

	// 공격 영역 비활성화
	void DisableAttackArea();


		
};
