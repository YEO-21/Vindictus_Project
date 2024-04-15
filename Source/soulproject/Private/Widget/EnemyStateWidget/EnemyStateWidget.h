// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEnemyStateWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	// 적 이름 위젯
	UPROPERTY()
	class UTextBlock * TextBlock_EnemyName;

	// Hp 위젯
	UPROPERTY()
	class UProgressBar* Progressbar_Hp;

private :
	// 표시하는 타깃 적 객체를 나타냅니다.
	UPROPERTY()
	class AEnemyCharacter* TargetEnemy;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& myGeometry, float dt) override;
	

public :
	// 타깃 적을 갱신합니다.
	void UpdateTargetEnemy(class AEnemyCharacter* newTargetEnemy);

	
};
