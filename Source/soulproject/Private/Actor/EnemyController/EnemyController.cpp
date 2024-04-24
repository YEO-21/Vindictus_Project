#include "Actor/EnemyController/EnemyController.h"
#include "Actor/GameCharacter/GameCharacter.h"

#include "Structure/EnemyData/EnemyData.h"
#include "Structure/PlayerCharacterData/PlayerCharacterData.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "../soulproject.h"

void AEnemyController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	// Get BlackboardComponent
	BlackBoardComponent = GetBlackboardComponent();

	// ������ Ű �ʱ�ȭ
	OnBlackboardKeyInitialize(BlackBoardComponent, inPawn);
}

void AEnemyController::OnBlackboardKeyInitialize(UBlackboardComponent* blackboardComponent, APawn* inPawn)
{
	// SpawnLocation ����
	FVector spawnLocation = inPawn->GetActorLocation();
	blackboardComponent->SetValueAsVector(BLACKBOARDKEY_SPAWNLOCATION, spawnLocation);

	// ������ ���°� Ǯ������� �ɸ��� �ð� ����
	blackboardComponent->SetValueAsFloat(BLACKBOARDKEY_TIMETOCALMDOWN, 10.0f);
}

void AEnemyController::InitializeEnemyController(FEnemyData * enemyData)
{
	if (enemyData == nullptr) return;

	FStreamableManager& streamableManager = UAssetManager::GetStreamableManager();

	// BehaviorTree ������ ���� �ε� ��ŵ�ϴ�.
	UBehaviorTree* btAsset = enemyData->BehaviorTreeAsset;
		//Cast<UBehaviorTree>(streamableManager.LoadSynchronous(
		//enemyData->BehaviorTreeAsset.ToSoftObjectPath()));

	// �ε�� BehaviorTree ���¿� ���� ��ȿ�� �˻縦 �����մϴ�.
	if (IsValid(btAsset))
	{
		// �ൿ Ʈ���� �����մϴ�.
		RunBehaviorTree(btAsset);

		UE_LOG(LogTemp, Warning, TEXT("Start BehaviorTree!"));
	}
}

void AEnemyController::OnDamaged(AGameCharacter* gameCharacter, float damage)
{
	if (!IsValid(BlackBoardComponent)) return;

	// �������� ���·� ����
	BlackBoardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, true);

	// ���ݴ��� �ð� ����
	float currentTimeSeconds = UGameplayStatics::GetTimeSeconds(this);
	BlackBoardComponent->SetValueAsFloat(BLACKBOARDKEY_LASTDAMAGEDTIME, currentTimeSeconds);

	// ������ ���� ���� (GameCharacter ����)
	BlackBoardComponent->SetValueAsObject(BLACKBOARDKEY_DAMAGEACTOR, gameCharacter);
}

void AEnemyController::OnDead()
{
	BlackBoardComponent->SetValueAsBool(BLACKBOARDKEY_ISDEAD, true);

	BlackBoardComponent->GetBrainComponent()->StopLogic(FString());
}

void AEnemyController::OnPlayerDead()
{
	BlackBoardComponent->SetValueAsBool(BLACKBOARDKEY_ISPLAYERDEAD, true);

	BlackBoardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, false);

}

void AEnemyController::OnPlayerRespawn()
{
	BlackBoardComponent->SetValueAsBool(BLACKBOARDKEY_ISPLAYERDEAD, false);
}
