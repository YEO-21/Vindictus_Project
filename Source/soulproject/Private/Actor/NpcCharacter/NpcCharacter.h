// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NpcCharacter.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnInteractionFinishSignature)

UCLASS()
class ANpcCharacter : public ACharacter
{
	GENERATED_BODY()


private :
	FOnInteractionFinishSignature OnInteractionFinished;

	UPROPERTY()
	class UDataTable* DT_NpcData;

protected :
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* NpcWidgetComponent;

	// 상호작용 가능한 영역
	UPROPERTY(VisibleAnywhere)
	class UInteractableAreaComponent * InteractableAreaComponent;

	// 상호작용 시 플레이어 캐릭터가 배치될 위치
	UPROPERTY(VisibleAnywhere)
	class USceneComponent * InteractionLocation;

	// 상호작용 시 설정될 뷰 카메라
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent * InteractionViewTargetCamera;

	
	// NPC 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NpcCode;

	// Npc 정보
	struct FNpcData* NpcData;

	// 생성된 Npc Dialog Widget 객체
	UPROPERTY()
	class UNpcDialogWidget* NpcDialogWidget;


public:
	ANpcCharacter();

protected:
	virtual void BeginPlay() override;

	// Npc 데이터를 초기화합니다.
	virtual void InitializeNpcData();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished);

	FORCEINLINE class UNpcDialogWidget* GetNpcDialogWidget() const
	{
		return NpcDialogWidget;
	}

	FORCEINLINE class UCameraComponent* GetInteractionViewTarget() const
	{
		return InteractionViewTargetCamera;
	}

	// 상호작용 시 배치될 월드 위치를 얻습니다.
	FVector GetInteractionLocation() const;

	// 상호작용 시 배치될 월드 회전을 얻습니다.
	FRotator GetInteractionRotation() const;

};
