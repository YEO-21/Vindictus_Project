#include "Widget/EnemyStateWidget/EnemyStateWidget.h"

#include "Actor/EnemyCharacter/EnemyCharacter.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Structure/EnemyData/EnemyData.h"

void UEnemyStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock_EnemyName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_EnemyName")));
	Progressbar_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("Progressbar_Hp")));
}

void UEnemyStateWidget::NativeTick(const FGeometry& myGeometry, float dt)
{
	Super::NativeTick(myGeometry, dt);

	// 적 유효함
	bool targetEnemyIsValid = IsValid(TargetEnemy);

	// 적 사망함
	bool enemyIsDead = false;
	if (targetEnemyIsValid) enemyIsDead = TargetEnemy->IsDeadState();


	// 목표 적 캐릭터가 유효하며 사망하지 않았을 경우
	if (targetEnemyIsValid && !enemyIsDead)
	{
		// 적 정보를 얻습니다.
		const FEnemyData* enemyData = TargetEnemy->GetEnemyData();

		// 현재 체력을 얻습니다.
		float currentHp = TargetEnemy->GetCurrentHp();

		// 표시 이름 설정
		TextBlock_EnemyName->SetText(enemyData->Name);

		// 현재 HP 설정
		Progressbar_Hp->SetPercent(currentHp / enemyData->MaxHP);
	}
	// 유효하지 않은 경우
	else
	{
		// 목표 적 nullptr
		TargetEnemy = nullptr;

		// 위젯을 숨깁니다.
		SetVisibility(ESlateVisibility::Collapsed);
	}

}

void UEnemyStateWidget::UpdateTargetEnemy(AEnemyCharacter* newTargetEnemy)
{
	TargetEnemy = newTargetEnemy;
}
