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

	// 컨트롤러를 얻습니다.
	AController* ownerController = Cast<AController>(OwnerComp.GetOwner());

	// 컨트롤러가 조종하는 액터
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

	// 타깃 액터를 얻습니다.
	UObject* targetActorObject = blackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName);

	if (!IsValid(targetActorObject)) return EBTNodeResult::Failed;
	// 유효성 검사
	AActor* targetActor = Cast<AActor>(targetActorObject);

	// 컨트롤러를 얻습니다.
	AController* ownerController = Cast<AController>(blackboardComponent->GetOwner());

	// 유효성 검사
	if (!IsValid(ownerController)) return EBTNodeResult::Failed;

	// 컨트롤러가 조종하는 액터
	ADragonCharacter* controlledPawn = Cast<ADragonCharacter>(ownerController->GetPawn());



	// 해당 액터로 향하는 방향을 얻습니다.
	FVector direction = targetActor->GetActorLocation() - controlledPawn->GetActorLocation();
	direction.Z = 0.0f;
	direction = direction.GetSafeNormal();

	// 각도를 계산합니다.
	float yawAngle = FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X));

	

	// 현재 회전과 별 차이가 없는 경우, 회전시키지 않습니다.
	float currentYawAngle = controlledPawn->GetActorRotation().Yaw;
	if (FRotator(0.0f, yawAngle, 0.0f).Equals(FRotator(0.0f, currentYawAngle, 0.0f), 15.0f))
	{
		return EBTNodeResult::Type::Succeeded;
	}


	// 계산한 각도를 설정합니다.
	controlledPawn->GetDragonMovementComponent()->SetTargetYawAngle(yawAngle);



	// 애니메이션 몽타주 재생
	controlledPawn->PlayMoveAnimMontage(
		yawAngle > 0.0f ?
		ANIMMONTAGE_SECTION_TURNRIGHT : ANIMMONTAGE_SECTION_TURNLEFT);

	return EBTNodeResult::Type::InProgress;
}
