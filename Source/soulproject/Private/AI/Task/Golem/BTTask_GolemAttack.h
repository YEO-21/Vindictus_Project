#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GolemAttack.generated.h"

UCLASS()
class UBTTask_GolemAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// ���� ��û�� Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackRequestedKey;

	// ������ Ű
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsAttackingKey;

public:
	UBTTask_GolemAttack();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* newMemory) override;

};
