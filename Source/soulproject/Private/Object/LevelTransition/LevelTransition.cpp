#include "Object/LevelTransition/LevelTransition.h"

#include "Object/SaveGame/FirstSaveGame.h"
#include "Object/LevelTransition/LevelTransitionGameInstance/LevelTransitionGameInstance.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"

#include "Kismet/GameplayStatics.h"

ALevelTransition::ALevelTransition()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ALevelTransition::BeginPlay()
{
	Super::BeginPlay();
	
	//// Get Controller
	AGamePlayerController* playerController = Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());
	OwnerCharacter = Cast<AGameCharacter>(playerController->GetPawn());

}

void ALevelTransition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ALevelTransition::SaveData()
{
	OwnerCharacter->SetGameInstance();

}

void ALevelTransition::LoadData()
{
	OwnerCharacter->UpdateGameInstance();

}

