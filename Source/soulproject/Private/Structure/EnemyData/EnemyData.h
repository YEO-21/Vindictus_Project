// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

/**
 * �� ������ ��Ÿ���� ���� ����ü�Դϴ�.
 */
USTRUCT()
struct FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// �� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHP;

	// ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Atk;


	// ���� ���� Ŭ������ ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> EnemyHUDClass;


	// �ൿ Ʈ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* BehaviorTreeAsset;
	//TSoftObjectPtr<class UBehaviorTree> BehaviorTreeAsset;
	// FSoftObjectPath : ���� ����, �񵿱� �ε带 ���Ͽ� ��θ� ������ �� �ִ� ����
	// TSoftObjectPtr �� FSoftObjectPath �� Wrapper �����̸�, ���ø��� ���� 
	// ������ ���¸� ������ �� �ִ� ����� �����մϴ�.
	// �� �� ������ ���� ������ ������ ��� ���ڿ��� �Է��ϴ� ��ſ� ������ �����Ͽ� ��θ� ������ �� �ֽ��ϴ�.
	// �̷��� �����س��� ��δ� StreamableManager�� ���� �񵿱������� �ε��ų �� �ս��ϴ�.

	// ��� �� ������ų ���͸��� �ν��Ͻ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstance * MaterialInstanceOnDead;



};
