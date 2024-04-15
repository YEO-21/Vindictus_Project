#include "Actor/EnemyController/Dragon/DragonController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

void ADragonController::SetPlayerCharacterKey(AGameCharacter* playerCharacter)
{
	BlackBoardComponent->SetValueAsObject(KEYNAME_PLAYERCHARACTER, playerCharacter);
}

void ADragonController::OnDashFinished()
{
	BlackBoardComponent->SetValueAsBool(KEYNAME_ISMOVETASKRUNNING, false);
}

void ADragonController::UpdateCurrentHp(float currentHp)
{
	BlackBoardComponent->SetValueAsFloat(KEYNAME_CURRENTHP, currentHp);
}
