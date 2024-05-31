#include "Structure/EnemyData/EnemyData.h"

FEnemyData::FEnemyData()
{
	Name = FText::FromString(TEXT(""));
	MaxHP = 0.0f;
	Atk = 0.0f;

	EnemyHUDClass = nullptr;
	BehaviorTreeAsset = nullptr;
	MaterialInstanceOnDead = nullptr;
}
