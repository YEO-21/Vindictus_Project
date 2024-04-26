#include "Component/NpcWeaponExchangeComponent/NpcWeaponExchangeComponent.h"

#include "Actor/NpcCharacter/NpcCharacter.h"

UNpcWeaponExchangeComponent::UNpcWeaponExchangeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UNpcWeaponExchangeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UNpcWeaponExchangeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


