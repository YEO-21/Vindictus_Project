#include "AI/Task/Common/BTTask_UpdateDistanceToPlayer.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_UpdateDistanceToPlayer::UBTTask_UpdateDistanceToPlayer()
{
	PlayerCharacterActorKey.AddObjectFilter(this,
		GET_MEMBER_NAME_CHECKED(ThisClass, PlayerCharacterActorKey),
		UObject::StaticClass());

	DistanceToPlayerKey.AddFloatFilter(this,
		GET_MEMBER_NAME_CHECKED(ThisClass, DistanceToPlayerKey));
}

EBTNodeResult::Type UBTTask_UpdateDistanceToPlayer::ExecuteTask(
	UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	// Get BlackboardComponent
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// �� �ൿ�� �����ϴ� ��ü(��Ʈ�ѷ�)
	AController* ownerController = Cast<AController>(ownerComponent.GetOwner());

	// ��ȿ�� �˻�
	if (!IsValid(ownerController)) return EBTNodeResult::Type::Failed;

	// �� �ൿ�� �����ϴ� ����(�� ĳ����)
	AActor* controlledPawn = ownerController->GetPawn();

	// ��ȿ�� �˻�
	if (!IsValid(controlledPawn)) return EBTNodeResult::Type::Failed;

	// �÷��̾� ĳ���� ����
	UObject * value = blackboardComponent->GetValueAsObject(
		PlayerCharacterActorKey.SelectedKeyName);

	// ��ȿ�� �˻�
	if (!IsValid(value)) return EBTNodeResult::Type::Failed;

	AGameCharacter* gameCharacter = Cast<AGameCharacter>(value);

	// �Ÿ��� ����մϴ�.
	FVector gameCharacterLocation = gameCharacter->GetActorLocation();
	gameCharacterLocation.Z = 0.0f;

	FVector ownerCharacterLocation = controlledPawn->GetActorLocation();
	ownerCharacterLocation.Z = 0.0f;

	float distance = FVector::Distance(gameCharacterLocation, ownerCharacterLocation);

	// ���� �Ÿ��� Ű�� �����մϴ�.
	blackboardComponent->SetValueAsFloat(
		DistanceToPlayerKey.SelectedKeyName,
		distance);




	// �ൿ ���� ����
	return EBTNodeResult::Type::Succeeded;
}
