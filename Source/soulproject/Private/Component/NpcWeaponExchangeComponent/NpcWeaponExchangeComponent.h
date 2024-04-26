#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NpcWeaponExchangeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNpcWeaponExchangeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNpcWeaponExchangeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
