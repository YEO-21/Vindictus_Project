#include "Component/BossCriticalAttackComponent/BossCriticalAttackComponent.h"

#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Component/PlayerCharacterAttackComponent/PlayerCharacterAttackComponent.h"

#include "Structure/EnemyData/EnemyData.h"

#include "Widget/GameWidget/GameWidget.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBossCriticalAttackComponent::UBossCriticalAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBossCriticalAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UBossCriticalAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CheckBossHp()) ShowCriticalAttackWidget();

}

void UBossCriticalAttackComponent::ApplyCriticalDamage()
{
	//UGameplayStatics::ApplyPointDamage()
}

bool UBossCriticalAttackComponent::CheckBossHp()
{
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	if (!IsValid(gameCharacter)) return false;

	// 게임 플레이어가 공격한 적 객체를 얻습니다.
	AEnemyCharacter* enemy = gameCharacter->GetAttackComponent()->enemyCharacter;
	if (!IsValid(enemy)) return false;

	FName enemyCode = enemy->GetEnemyCode();
	float currentHp = enemy->GetCurrentHp();
	float maxHp = enemy->GetEnemyData()->MaxHP;

	

	return (enemyCode == TEXT("000004") && (currentHp / maxHp) < 0.3f);
}

void UBossCriticalAttackComponent::ShowCriticalAttackWidget()
{
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	AGamePlayerController* controller = Cast<AGamePlayerController>(gameCharacter->GetController());

	if (!IsValid(controller)) return;

	controller->GetGameWidget()->ShowCriticalWidget();
}



