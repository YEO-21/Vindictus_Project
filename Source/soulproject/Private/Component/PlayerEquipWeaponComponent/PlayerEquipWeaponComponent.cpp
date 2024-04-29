#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"

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
	WeaponCode = Cast<AGameCharacter>(GetOwner())->EquippedWeaponCode;
	UE_LOG(LogTemp, Warning, TEXT("WeaponCode = %s"), *WeaponCode.ToString());
	if (WeaponCode.IsNone())
	{
		PlayerWeaponData = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("WeaponCode is not valid!"));
		return;
	}

	FString contextstring;
	PlayerWeaponData = DT_WeaponData->FindRow<FPlayerWeaponData>(WeaponCode, contextstring);


}

void UPlayerEquipWeaponComponent::CheckCurrentMainWeapon()
{
	InitializeEquippedWeapon();
	
}


void UPlayerEquipWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerEquipWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerEquipWeaponComponent::EquipWeapon()
{
	CheckCurrentMainWeapon();

	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	UPlayerCharacterAnimInstance* animInst = 
		Cast<UPlayerCharacterAnimInstance>(playerCharacter->GetMesh()->GetAnimInstance());

	if (PlayerWeaponData == nullptr) return;

	switch (PlayerWeaponData->WeaponType)
	{
	case EWeaponType::SHARPNER:
		playerCharacter->GetWeaponMesh()->SetStaticMesh(PlayerWeaponData->WeaponStaticMesh);
		animInst->SetOneHandedWeapon(false);
		break;
	case EWeaponType::STORM_BREAKER:
		playerCharacter->GetSubWeaponMesh()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetOneHandedWeapon(false);
		break;
	case EWeaponType::TWIN_DRAGON_SWORD:
		playerCharacter->GetSubWeaponMesh()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetOneHandedWeapon(true);
		break;
		
	}
}

