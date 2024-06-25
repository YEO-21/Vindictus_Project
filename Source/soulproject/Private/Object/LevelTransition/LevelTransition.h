
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransition.generated.h"

UCLASS()
class ALevelTransition : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class AGameCharacter* OwnerCharacter;

	UPROPERTY()
	class ULevelTransitionGameInstance* GameInstance; 
	
public:	
	ALevelTransition();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void SaveData();

	UFUNCTION(BlueprintCallable)
	void LoadData();

};
