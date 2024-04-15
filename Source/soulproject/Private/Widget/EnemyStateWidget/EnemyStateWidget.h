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
	// �� �̸� ����
	UPROPERTY()
	class UTextBlock * TextBlock_EnemyName;

	// Hp ����
	UPROPERTY()
	class UProgressBar* Progressbar_Hp;

private :
	// ǥ���ϴ� Ÿ�� �� ��ü�� ��Ÿ���ϴ�.
	UPROPERTY()
	class AEnemyCharacter* TargetEnemy;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& myGeometry, float dt) override;
	

public :
	// Ÿ�� ���� �����մϴ�.
	void UpdateTargetEnemy(class AEnemyCharacter* newTargetEnemy);

	
};
