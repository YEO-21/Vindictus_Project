// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enum/Npc/NpcType.h"
#include "NpcCharacter.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnInteractionFinishSignature)

UCLASS()
class ANpcCharacter : public ACharacter
{
	GENERATED_BODY()


private :
	FOnInteractionFinishSignature OnInteractionFinished;

	UPROPERTY()
	TSubclassOf<class UWalldoNpcWeaponWidget> BP_WallWeaponWidget;

	UPROPERTY()
	class UDataTable* DT_NpcData;

protected :

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* NpcWidgetComponent;

	// ��ȣ�ۿ� ������ ����
	UPROPERTY(VisibleAnywhere)
	class UInteractableAreaComponent * InteractableAreaComponent;

	// ��ȣ�ۿ� �� �÷��̾� ĳ���Ͱ� ��ġ�� ��ġ
	UPROPERTY(VisibleAnywhere)
	class USceneComponent * InteractionLocation;

	// ��ȣ�ۿ� �� ������ �� ī�޶�
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent * InteractionViewTargetCamera;

	// ���� ��ȯ ������Ʈ
	UPROPERTY(VisibleAnywhere)
	class UNpcWeaponExchangeComponent* WeaponExchangeComponent;

	
	// NPC �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NpcCode;

	// Npc ����
	struct FNpcData* NpcData;

	// ������ Npc Dialog Widget ��ü
	UPROPERTY()
	class UNpcDialogWidget* NpcDialogWidget;

	UPROPERTY()
	bool isfullfill;

	UPROPERTY()
	ENpcType NpcType;



public:
	ANpcCharacter();

protected:
	virtual void BeginPlay() override;

	// Npc �����͸� �ʱ�ȭ�մϴ�.
	virtual void InitializeNpcData();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished);

	virtual void FinishTalkAnimation();

	FORCEINLINE class UNpcDialogWidget* GetNpcDialogWidget() const
	{
		return NpcDialogWidget;
	}

	FORCEINLINE class UCameraComponent* GetInteractionViewTarget() const
	{
		return InteractionViewTargetCamera;
	}

	FORCEINLINE bool GetIsFullfill() const
	{
		return isfullfill;
	}

	FORCEINLINE ENpcType GetNpcType() const
	{
		return NpcType;
	}

	void SetIsFullfill(bool full);
	


	// ��ȣ�ۿ� �� ��ġ�� ���� ��ġ�� ����ϴ�.
	FVector GetInteractionLocation() const;

	// ��ȣ�ۿ� �� ��ġ�� ���� ȸ���� ����ϴ�.
	FRotator GetInteractionRotation() const;


	virtual class UInteractionParamBase* GetInteractionParam();

};
