#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GolemAttack.generated.h"

UCLASS()
class UBTTask_GolemAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// 공격 요청됨 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackRequestedKey;

	// 공격중 키
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackingKey;

public:
	UBTTask_GolemAttack();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;

};
