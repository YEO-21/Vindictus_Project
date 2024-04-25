#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"

#include "Structure/PlayerWeaponData/PlayerWeaponData.h"




UPlayerEquipWeaponComponent::UPlayerEquipWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WEAPON (
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_PlayerWeaponData.DT_PlayerWeaponData'"));

	if (DT_WEAPON.Succeeded()) DT_WeaponData = DT_WEAPON.Object;

}

void UPlayerEquipWeaponComponent::InitializeEquippedWeapon()
{
	if (WeaponCode.IsNone())
	{
		PlayerWeaponData = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("WeaponCode is not valid!"));
		return;
	}

	FString contextstring;
	PlayerWeaponData = DT_WeaponData->FindRow<FPlayerWeaponData>(WeaponCode, contextstring);

}

void UPlayerEquipWeaponComponent::CheckCurrentMainWeapon(AActor* actor, FName weaponCode)
{
	if (actor->ActorHasTag(weaponCode))
	{
		WeaponCode = weaponCode;
		InitializeEquippedWeapon();
	}
	
}


void UPlayerEquipWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerEquipWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

