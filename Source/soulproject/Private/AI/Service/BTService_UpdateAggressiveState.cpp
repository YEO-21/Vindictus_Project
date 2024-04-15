#include "AI/Service/BTService_UpdateAggressiveState.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateAggressiveState::UBTService_UpdateAggressiveState()
{
	IsAggressiveStateKey.AddBoolFilter(this, 
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateAggressiveState, IsAggressiveStateKey));

	LastDamagedTimeKey.AddFloatFilter(this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateAggressiveState, LastDamagedTimeKey));

	TimeToCalmDownKey.AddFloatFilter(this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateAggressiveState, TimeToCalmDownKey));

}

void UBTService_UpdateAggressiveState::TickNode(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickNode(ownerComponent, nodeMemory, deltaSeconds);

	// Get BlackboardComponent
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// 공격적인 상태
	bool isAggressiveState = blackboardComponent->GetValueAsBool(IsAggressiveStateKey.SelectedKeyName);

	// 마지막으로 피해를 입은 시간
	float lastDamagedTimeSeconds = blackboardComponent->GetValueAsFloat(LastDamagedTimeKey.SelectedKeyName);

	// 공격적 상태가 끝나기까지 걸리는 시간
	float timeToCalmDown = blackboardComponent->GetValueAsFloat(TimeToCalmDownKey.SelectedKeyName);

	// 현재 시간
	float currentTimeSeconds = UGameplayStatics::GetTimeSeconds(ownerComponent.GetOwner());

	// 공격적 상태가 끝나는 시간이 경과된 경우
	if (isAggressiveState &&
		currentTimeSeconds >= lastDamagedTimeSeconds + timeToCalmDown)
	{
		// 공격 상태 끝
		blackboardComponent->SetValueAsBool(IsAggressiveStateKey.SelectedKeyName, false);
	}
}
