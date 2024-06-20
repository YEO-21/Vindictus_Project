#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "NiagaraSystem/AttackNiagaraSystem.h"

#include "Widget/StoreItemWidget/StoreItemWidget.h"
#include "Widget/WeaponStoreWidget/WeaponStoreWidget.h"
#include "Widget/PlayerWeaponStateWidget/PlayerWeaponStateWidget.h"

#include "Object/LevelTransition/LevelTransitionGameInstance/LevelTransitionGameInstance.h"

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

	// 기본 무기 코드 설정
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());
	playerCharacter->EquippedWeaponCode = _SHARPNER;

	

	
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

	// Get Controller
	AGamePlayerController* playerController =
		Cast<AGamePlayerController>(playerCharacter->GetController());


	InitializeEquippedWeapon(playerCharacter->EquippedWeaponCode);


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
		UE_LOG(LogTemp, Warning, TEXT("EquipAxe"));
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

	// 무기 타입에 따른 이펙트를 설정합니다.
	playerCharacter->GetAttackNiagaraSystem()->SetNiagaraSystemAsset(
		PlayerWeaponData->AttackEffect, PlayerWeaponData->AttackHitEffect);

	// 무기 상태 위젯의 이미지 설정
	UpdateWeaponStateTexture.ExecuteIfBound(PlayerWeaponData->WidgetWeaponImage);


}

bool UPlayerEquipWeaponComponent::IsSpearWeapon() const
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());
	FName weaponCode = playerCharacter->EquippedWeaponCode;

	return (weaponCode ==_WALLDO) || (weaponCode == _NAMELESSSPEAR);
}

void UPlayerEquipWeaponComponent::InitializeUpdateWeaponImageEvent(FUpdateTextureEventSignature event)
{
	UpdateWeaponStateTexture = event;
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



