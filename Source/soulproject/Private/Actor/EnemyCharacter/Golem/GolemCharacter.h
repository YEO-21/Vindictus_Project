#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "GolemCharacter.generated.h"

UCLASS()
class AGolemCharacter : public AEnemyCharacter
{
	GENERATED_BODY()


private:
	UPROPERTY()
	class USkeletalMeshComponent* GolemSkeletalMesh;
	

public:
	AGolemCharacter();


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float dt) override;


};
