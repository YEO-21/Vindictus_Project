#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerEquipWeaponComponent.generated.h"

// 무기 코드
#define _SHARPNER			TEXT("000001")
#define _STORMBREAKER		TEXT("000002")
#define _TWINDRAGONSWORD	TEXT("000003")
#define _WALLDO				TEXT("000004")
#define _NAMELESSSPEAR		TEXT("000005")




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerEquipWeaponComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	struct FPlayerWeaponData* PlayerWeaponData;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponCode;

	UPROPERTY()
	class UDataTable* DT_WeaponData;

	UPROPERTY()
	TSubclassOf<class UWeaponStoreWidget> BP_WeaponStoreWidget;

	UPROPERTY()
	class UWeaponStoreWidget* WeaponStoreWidget;




public:	
	UPlayerEquipWeaponComponent();

	void InitializeEquippedWeapon(FName weaponCode);


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION()
	void EquipWeapon();

	UDataTable* GetWeaponData() const
	{
		return DT_WeaponData;
	}

	bool IsSpearWeapon() const;
	

	

private:
	int32 CheckWeaponType();

};
