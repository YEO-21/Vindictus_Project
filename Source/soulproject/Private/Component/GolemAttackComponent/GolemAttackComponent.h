#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GolemAttackComponent.generated.h"


#define SOCKETNAME_LEFTHANDSTART		TEXT("Socket_LeftHandStart")
#define SOCKETNAME_LEFTHANDEND			TEXT("Socket_LeftHandEnd")
#define SOCKETNAME_RIGHTHANDSTART		TEXT("Socket_RightHandStart")
#define SOCKETNAME_RIGHTHANDEND			TEXT("Socket_RightHandEnd")


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGolemAttackComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bEnableAttack;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class AGolemController* GolemController;


public:	
	UGolemAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack(FName sectionName);

	void EnableAttackArea();
	void DisableAttackArea();
};
