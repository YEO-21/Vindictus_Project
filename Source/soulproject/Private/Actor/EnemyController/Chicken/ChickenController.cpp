#include "Actor/EnemyController/Chicken/ChickenController.h"

#include "BehaviorTree/BlackboardComponent.h"

void AChickenController::OnBlackboardKeyInitialize(UBlackboardComponent* blackboardComponent, APawn* inPawn)
{
	Super::OnBlackboardKeyInitialize(blackboardComponent, inPawn);

	// MaxMoveDistance ¼³Á¤
	blackboardComponent->SetValueAsFloat(BLACKBOARDKEY_MAXMOVEDISTANCE, 200.0f);
}
