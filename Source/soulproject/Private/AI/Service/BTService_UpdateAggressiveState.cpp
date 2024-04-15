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

	// �������� ����
	bool isAggressiveState = blackboardComponent->GetValueAsBool(IsAggressiveStateKey.SelectedKeyName);

	// ���������� ���ظ� ���� �ð�
	float lastDamagedTimeSeconds = blackboardComponent->GetValueAsFloat(LastDamagedTimeKey.SelectedKeyName);

	// ������ ���°� ��������� �ɸ��� �ð�
	float timeToCalmDown = blackboardComponent->GetValueAsFloat(TimeToCalmDownKey.SelectedKeyName);

	// ���� �ð�
	float currentTimeSeconds = UGameplayStatics::GetTimeSeconds(ownerComponent.GetOwner());

	// ������ ���°� ������ �ð��� ����� ���
	if (isAggressiveState &&
		currentTimeSeconds >= lastDamagedTimeSeconds + timeToCalmDown)
	{
		// ���� ���� ��
		blackboardComponent->SetValueAsBool(IsAggressiveStateKey.SelectedKeyName, false);
	}
}
