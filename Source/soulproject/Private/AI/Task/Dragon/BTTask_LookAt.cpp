#include "AI/Task/Dragon/BTTask_LookAt.h"

#include "Actor/EnemyCharacter/Dragon/DragonCharacter.h"
#include "Component/DragonCharacterMovementComponent/DragonCharacterMovementComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_LookAt::UBTTask_LookAt()
{
	IsMoveTaskRunningKey.AddBoolFilter(this,
		GET_MEMBER_NAME_CHECKED(ThisClass, IsMoveTaskRunningKey));

	TargetActorKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, TargetActorKey),
		UObject::StaticClass());

	bNotifyTick = true;
}

void UBTTask_LookAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// ��Ʈ�ѷ��� ����ϴ�.
	AController* ownerController = Cast<AController>(OwnerComp.GetOwner());

	// ��Ʈ�ѷ��� �����ϴ� ����
	ADragonCharacter* controlledPawn = Cast<ADragonCharacter>(ownerController->GetPawn());

	UDragonCharacterMovementComponent* movementComponent = controlledPawn->GetDragonMovementComponent();

	if (!YawTerningStarted)
	{
		if (movementComponent->GetYawTurningState())
			YawTerningStarted = true;
		else return;
	}

	if (controlledPawn->GetDragonMovementComponent()->IsYawTernFinished())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		YawTerningStarted = false;
	}
}

EBTNodeResult::Type UBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* newMemory)
{
	UBlackboardComponent* blackboardComponent = ownerComponent.GetBlackboardComponent();

	// Ÿ�� ���͸� ����ϴ�.
	UObject* targetActorObject = blackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName);

	if (!IsValid(targetActorObject)) return EBTNodeResult::Failed;
	// ��ȿ�� �˻�
	AActor* targetActor = Cast<AActor>(targetActorObject);

	// ��Ʈ�ѷ��� ����ϴ�.
	AController* ownerController = Cast<AController>(blackboardComponent->GetOwner());

	// ��ȿ�� �˻�
	if (!IsValid(ownerController)) return EBTNodeResult::Failed;

	// ��Ʈ�ѷ��� �����ϴ� ����
	ADragonCharacter* controlledPawn = Cast<ADragonCharacter>(ownerController->GetPawn());



	// �ش� ���ͷ� ���ϴ� ������ ����ϴ�.
	FVector direction = targetActor->GetActorLocation() - controlledPawn->GetActorLocation();
	direction.Z = 0.0f;
	direction = direction.GetSafeNormal();

	// ������ ����մϴ�.
	float yawAngle = FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X));

	

	// ���� ȸ���� �� ���̰� ���� ���, ȸ����Ű�� �ʽ��ϴ�.
	float currentYawAngle = controlledPawn->GetActorRotation().Yaw;
	if (FRotator(0.0f, yawAngle, 0.0f).Equals(FRotator(0.0f, currentYawAngle, 0.0f), 15.0f))
	{
		return EBTNodeResult::Type::Succeeded;
	}


	// ����� ������ �����մϴ�.
	controlledPawn->GetDragonMovementComponent()->SetTargetYawAngle(yawAngle);



	// �ִϸ��̼� ��Ÿ�� ���
	controlledPawn->PlayMoveAnimMontage(
		yawAngle > 0.0f ?
		ANIMMONTAGE_SECTION_TURNRIGHT : ANIMMONTAGE_SECTION_TURNLEFT);

	return EBTNodeResult::Type::InProgress;
}
