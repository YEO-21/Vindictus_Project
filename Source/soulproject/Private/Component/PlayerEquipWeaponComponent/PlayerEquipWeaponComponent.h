#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerEquipWeaponComponent.generated.h"


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
	TSubclassOf<UWeaponStoreWidget> BP_WeaponStoreWidget;

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

private:
	void TransitionToSpear();

};
