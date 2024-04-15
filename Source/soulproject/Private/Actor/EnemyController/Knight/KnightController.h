#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyController/EnemyController.h"
#include "Perception/AIPerceptionTypes.h"
#include "KnightController.generated.h"

#define KEYNAME_ISATTACKING				TEXT("IsAttacking")

DECLARE_EVENT(AKnightController, FSigntDetectedEvent)

/**
 * 
 */
UCLASS()
class AKnightController : public AEnemyController
{
	GENERATED_BODY()

public :
	FSigntDetectedEvent OnSightDetected;
	FSigntDetectedEvent OnSightLose;

private :
	class UBlackboardComponent* BlackboardComponent;

	class UAISenseConfig_Sight* AISightConfig;

protected :
	virtual void OnBlackboardKeyInitialize(
		class UBlackboardComponent* blackboardComponent, 
		class APawn* inPawn) override;

public :
	AKnightController();
	void Attack();
	void OnAttackFinished();

private :
	// 시야 감지 상태가 변경될 때마다 발생하는 이벤트에 바인딩되는 함수
	UFUNCTION()
	void OnSightUpdated(class AActor* actor, FAIStimulus stimulus);


	
};
