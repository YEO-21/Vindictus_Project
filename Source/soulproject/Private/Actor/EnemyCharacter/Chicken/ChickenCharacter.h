#pragma once

#include "CoreMinimal.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "ChickenCharacter.generated.h"


/**
 * 
 */
UCLASS()
class AChickenCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
private :
	class UAnimMontage* OnHitAnimMontage;

public :
	AChickenCharacter();

public:
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float dt) override;

protected :
	virtual void OnDamaged(class AGameCharacter* gameCharacter, float damage) override;
	

private :
	// �ִ� �ν��Ͻ� �Ķ���͸� �����մϴ�.
	void UpdateAnimInstanceParams();

};
