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



	//// ���� �ν��Ͻ��� ����ϴ�.
	//SaveGameInstance =
	//	Cast<ULevelTransitionGameInstance>(UGameplayStatics::CreateSaveGameObject(ULevelTransitionGameInstance::StaticClass()));


	//// ���� �ڵ� ���
	//SaveGameInstance->CurrentWeaponCode = OwnerCharacter->GetCurrentWeaponCode();

	//// ���� ���� �ڵ� ���
	//SaveGameInstance->EquippedWeaponCode= OwnerCharacter->EquippedWeaponCode;


	//// ���� ü�� ���
	//SaveGameInstance->CurrentHp = OwnerCharacter->GetCurrentHp();

	//// ���� ���׹̳� ���
	//SaveGameInstance->CurrentStamina = playerController->GetCurrentStamina();

	//// ���� ���� ���
	////SaveGameInstance->Buff = playerController->SupplyInteractionItems;

	//// ���Կ� ����
	////bool isSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameCharacter", 0);

	////UE_LOG(LogTemp, Warning, TEXT("isSaved = %d"), isSaved);

	

}

void ALevelTransition::LoadData()
{
	OwnerCharacter->UpdateGameInstance();

	//// Get Controller
	//// �÷��̾� ĳ���� ��ü�� ����ϴ�.
	//AGamePlayerController* playerController = Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());
	//OwnerCharacter = Cast<AGameCharacter>(playerController->GetPawn());


	//// ���Կ��� ���� �ҷ�����
	////SaveGameInstance = Cast<UFirstSaveGame>(UGameplayStatics::LoadGameFromSlot("GameCharacter", 0));

	//// ���� �ڵ� ����
	//OwnerCharacter->SetCurrentWeaponCode(SaveGameInstance->CurrentWeaponCode);

	//// ���� ���� �ڵ� ����
	//OwnerCharacter->EquippedWeaponCode = SaveGameInstance->EquippedWeaponCode;
	//OwnerCharacter->GetEquipWeaponComponent()->EquipWeapon();

	//// ���� ü�� ����
	//OwnerCharacter->SetCurrentHp(SaveGameInstance->CurrentHp);

	//// ���� ���׹̳� ����
	//playerController->SetCurrentStamina(SaveGameInstance->CurrentStamina);

	//// ���� ���� ����
	////playerController->SupplyInteractionItems = SaveGameInstance->Buff;

	//UE_LOG(LogTemp, Warning, TEXT("LoadData"));

}

