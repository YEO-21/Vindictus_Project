#include "Actor/GameCharacter/GameCharacter.h"

#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "Widget/StoreItemWidget/StoreItemWidget.h"
#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"

#include "Structure/PlayerWeaponData/PlayerWeaponData.h"




UPlayerEquipWeaponComponent::UPlayerEquipWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WEAPON (
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_PlayerWeaponData.DT_PlayerWeaponData'"));

	if (DT_WEAPON.Succeeded()) DT_WeaponData = DT_WEAPON.Object;

	static ConstructorHelpers::FClassFinder<UWeaponStoreWidget> BP_WEAPON_STORE(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/WeaponStoreWidget/WidgetBP_WeaponStore.WidgetBP_WeaponStore_C'"));

	if (BP_WEAPON_STORE.Succeeded()) BP_WeaponStoreWidget = BP_WEAPON_STORE.Class;



}

void UPlayerEquipWeaponComponent::InitializeEquippedWeapon(FName weaponCode)
{
	WeaponCode = weaponCode;
	//UE_LOG(LogTemp, Warning, TEXT("WeaponCode = %s"), *WeaponCode.ToString());
	if (WeaponCode.IsNone())
	{
		PlayerWeaponData = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("WeaponCode is not valid!"));
		return;
	}

	FString contextstring;
	PlayerWeaponData = DT_WeaponData->FindRow<FPlayerWeaponData>(WeaponCode, contextstring);


}



void UPlayerEquipWeaponComponent::BeginPlay()
{
	Super::BeginPlay();


	//WeaponStoreWidget = CreateWidget<UWeaponStoreWidget>(GetWorld()->GetFirstPlayerController(), BP_WeaponStoreWidget);

	//PassWeaponWidgetSignature passWeaponEvent;
	//passWeaponEvent.AddLambda([this]() {
	//	EquipWeapon();
	//	UE_LOG(LogTemp, Warning, TEXT("passWeaponEvent"));
	//	});

	//WeaponStoreWidget->PassWeaponWidget.AddLambda([this]() {
	//	EquipWeapon();
	//	UE_LOG(LogTemp, Warning, TEXT("passWeaponEvent"));
	//	});

	//WeaponStoreWidget->InitializePassItemNameWidget(passWeaponEvent);

}


void UPlayerEquipWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerEquipWeaponComponent::EquipWeapon()
{
	// 무기가 창 종류라면 소켓 변경
	//TransitionToSpear();

	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	InitializeEquippedWeapon(playerCharacter->EquippedWeaponCode);
	UE_LOG(LogTemp, Warning, TEXT("playerCharacter->EquippedWeaponCode is %s"), *playerCharacter->EquippedWeaponCode.ToString());

	

	UPlayerCharacterAnimInstance* animInst = 
		Cast<UPlayerCharacterAnimInstance>(playerCharacter->GetMesh()->GetAnimInstance());

	if (PlayerWeaponData == nullptr) return;

	switch (PlayerWeaponData->WeaponType)
	{
	case EWeaponType::SHARPNER:
		playerCharacter->GetWeaponMesh()->SetStaticMesh(PlayerWeaponData->WeaponStaticMesh);
		animInst->SetOneHandedWeapon(false);
		animInst->SetSpear(false);
		break;
	case EWeaponType::STORM_BREAKER:
		playerCharacter->GetWeaponMeshOneHanded()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetOneHandedWeapon(false);
		animInst->SetSpear(false);
		break;
	case EWeaponType::TWIN_DRAGON_SWORD:
		playerCharacter->GetWeaponMeshOneHanded()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetOneHandedWeapon(true);
		animInst->SetSpear(false);
		break;
	case EWeaponType::WALLDO:
		playerCharacter->GetWeaponMeshSpear()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetSpear(true);
		break;
	case EWeaponType::NAMELESS_SPEAR:
		playerCharacter->GetWeaponMeshSpear()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetSpear(true);
		break;
	}

	// 장착할 무기 메시를 보이도록 설정합니다.
	playerCharacter->ShowWeaponMesh(CheckWeaponType());
	UE_LOG(LogTemp, Warning, TEXT("EquipWeapon is Called"));
}

bool UPlayerEquipWeaponComponent::IsSpearWeapon() const
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());
	FName weaponCode = playerCharacter->EquippedWeaponCode;

	return (weaponCode ==_WALLDO) || (weaponCode == _NAMELESSSPEAR);
}


int32 UPlayerEquipWeaponComponent::CheckWeaponType()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());
	FName weaponCode = playerCharacter->EquippedWeaponCode;

	// 창 무기 : 3 / 한손 무기 : 2 / 기본 무기 : 1 을 반환합니다.
	if (IsSpearWeapon())
		return 3;
	else if ((weaponCode == _STORMBREAKER) || (weaponCode == _TWINDRAGONSWORD))
		return 2;
	else return 1;

}

