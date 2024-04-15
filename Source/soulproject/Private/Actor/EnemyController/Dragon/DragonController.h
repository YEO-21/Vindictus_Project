#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyController/EnemyController.h"
#include "DragonController.generated.h"

#define KEYNAME_PLAYERCHARACTER			TEXT("PlayerCharacter")
#define KEYNAME_ISMOVETASKRUNNING		TEXT("IsMoveTaskRunning")
#define KEYNAME_CURRENTHP				TEXT("CurrentHp")

/**
 * 
 */
UCLASS()
class ADragonController : public AEnemyController
{
	GENERATED_BODY()
	




public :
	void SetPlayerCharacterKey(class AGameCharacter* playerCharacter);

	UFUNCTION()
	void OnDashFinished();

	void UpdateCurrentHp(float currentHp);


};
