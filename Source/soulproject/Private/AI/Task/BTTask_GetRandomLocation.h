#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_GetRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public :
	// 이 액터가 생성된 위치를 나타내는 Key 입니다.
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SpawnLocationKey;

	// 이동 가능한 최대 거리를 나타내는 Key
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector MaxMoveDistance;

	// 목표 위치를 저장할 Key
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector ResultLocationKey;

public : 
	UBTTask_GetRandomLocation();


public :
	// 태스크 실행 이벤트입니다.
	// return 을 통해 행동이 끝났음을 나타낼 수 있으며, EBTNodeResult::Type 를 통해 성공 여부를 반환할 수 있습니다.
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;
	
};
