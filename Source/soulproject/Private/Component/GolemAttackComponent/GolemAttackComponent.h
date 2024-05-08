#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GolemAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGolemAttackComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AttackAnimMontage;


public:	
	UGolemAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack(FName sectionName);
};
