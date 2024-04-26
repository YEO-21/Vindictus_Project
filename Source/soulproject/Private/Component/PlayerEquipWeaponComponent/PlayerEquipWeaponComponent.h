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





public:	
	UPlayerEquipWeaponComponent();

	void InitializeEquippedWeapon();

	void CheckCurrentMainWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void EquipWeapon();


};
