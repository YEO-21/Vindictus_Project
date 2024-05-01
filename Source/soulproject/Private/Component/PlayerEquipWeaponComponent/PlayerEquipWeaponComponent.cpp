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
	TransitionToSpear();

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
		break;
	case EWeaponType::STORM_BREAKER:
		playerCharacter->GetSubWeaponMesh()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetOneHandedWeapon(false);
		break;
	case EWeaponType::TWIN_DRAGON_SWORD:
		playerCharacter->GetSubWeaponMesh()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetOneHandedWeapon(true);
		break;
	case EWeaponType::WALLDO:
		playerCharacter->GetSubWeaponMesh()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetSpear(true);
		break;
	case EWeaponType::NAMELESS_SPEAR:
		playerCharacter->GetSubWeaponMesh()->SetSkeletalMesh(PlayerWeaponData->WeaponSkeletalMesh);
		animInst->SetSpear(true);
		break;

	}
	UE_LOG(LogTemp, Warning, TEXT("EquipWeapon is Called"));
}

void UPlayerEquipWeaponComponent::TransitionToSpear()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	FName equipeedWeaponCode = playerCharacter->EquippedWeaponCode;
	UE_LOG(LogTemp, Warning, TEXT("equipeedWeaponCode is %s"), *equipeedWeaponCode.ToString());

	if (equipeedWeaponCode == TEXT("000004") || equipeedWeaponCode == (TEXT("000005")))
	{
		UE_LOG(LogTemp, Warning, TEXT("TransitionToSpear is Called"));
		playerCharacter->GetSubWeaponMesh()->
			SetupAttachment(playerCharacter->GetMesh(), TEXT("Socket_Spear"));
	}
}

