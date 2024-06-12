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



	//// 저장 인스턴스를 얻습니다.
	//SaveGameInstance =
	//	Cast<ULevelTransitionGameInstance>(UGameplayStatics::CreateSaveGameObject(ULevelTransitionGameInstance::StaticClass()));


	//// 무기 코드 기록
	//SaveGameInstance->CurrentWeaponCode = OwnerCharacter->GetCurrentWeaponCode();

	//// 장착 무기 코드 기록
	//SaveGameInstance->EquippedWeaponCode= OwnerCharacter->EquippedWeaponCode;


	//// 현재 체력 기록
	//SaveGameInstance->CurrentHp = OwnerCharacter->GetCurrentHp();

	//// 현재 스테미너 기록
	//SaveGameInstance->CurrentStamina = playerController->GetCurrentStamina();

	//// 현재 버프 기록
	////SaveGameInstance->Buff = playerController->SupplyInteractionItems;

	//// 슬롯에 저장
	////bool isSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameCharacter", 0);

	////UE_LOG(LogTemp, Warning, TEXT("isSaved = %d"), isSaved);

	

}

void ALevelTransition::LoadData()
{
	OwnerCharacter->UpdateGameInstance();

	//// Get Controller
	//// 플레이어 캐릭터 객체를 얻습니다.
	//AGamePlayerController* playerController = Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController());
	//OwnerCharacter = Cast<AGameCharacter>(playerController->GetPawn());


	//// 슬롯에서 정보 불러오기
	////SaveGameInstance = Cast<UFirstSaveGame>(UGameplayStatics::LoadGameFromSlot("GameCharacter", 0));

	//// 무기 코드 갱신
	//OwnerCharacter->SetCurrentWeaponCode(SaveGameInstance->CurrentWeaponCode);

	//// 장착 무기 코드 갱신
	//OwnerCharacter->EquippedWeaponCode = SaveGameInstance->EquippedWeaponCode;
	//OwnerCharacter->GetEquipWeaponComponent()->EquipWeapon();

	//// 현재 체력 갱신
	//OwnerCharacter->SetCurrentHp(SaveGameInstance->CurrentHp);

	//// 현재 스테미나 갱신
	//playerController->SetCurrentStamina(SaveGameInstance->CurrentStamina);

	//// 현재 버프 갱신
	////playerController->SupplyInteractionItems = SaveGameInstance->Buff;

	//UE_LOG(LogTemp, Warning, TEXT("LoadData"));

}

