#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterInteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterInteractComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	// 상호작용 가능한 객체들
	TArray<class UInteractableAreaComponent*> InteractableAreas;

	// 상호작용 전 위치, 회전을 저장시켜 놓을 변수
	FVector BeforeInteractionLocation;
	FRotator BeforeInteractionRotation;

public:
	// 상호작용 시간
	UPROPERTY()
	float InteractTime;


public:	
	UPlayerCharacterInteractComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 상호작용 가능 영역 객체를 추가합니다.
	void AddInteractableArea(class UInteractableAreaComponent* newArea);

	// 상호작용 가능 영역 객체를 제거합니다.
	void RemoveInteractableArea(class UInteractableAreaComponent* newArea);

	// 상호작용 시도
	void TryInteraction();

private :
	void OnInteractionStarted(FVector interactionLocation, FRotator interactionRotation);
	void OnInteractionFinished();

	void RequestWeaponChange();

		
};
