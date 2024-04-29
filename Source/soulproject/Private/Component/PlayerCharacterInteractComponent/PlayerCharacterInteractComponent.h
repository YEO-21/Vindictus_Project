#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacterInteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerCharacterInteractComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	// ��ȣ�ۿ� ������ ��ü��
	TArray<class UInteractableAreaComponent*> InteractableAreas;

	// ��ȣ�ۿ� �� ��ġ, ȸ���� ������� ���� ����
	FVector BeforeInteractionLocation;
	FRotator BeforeInteractionRotation;

public:
	// ��ȣ�ۿ� �ð�
	UPROPERTY()
	float InteractTime;


public:	
	UPlayerCharacterInteractComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ��ȣ�ۿ� ���� ���� ��ü�� �߰��մϴ�.
	void AddInteractableArea(class UInteractableAreaComponent* newArea);

	// ��ȣ�ۿ� ���� ���� ��ü�� �����մϴ�.
	void RemoveInteractableArea(class UInteractableAreaComponent* newArea);

	// ��ȣ�ۿ� �õ�
	void TryInteraction();

private :
	void OnInteractionStarted(FVector interactionLocation, FRotator interactionRotation);
	void OnInteractionFinished();

	void RequestWeaponChange();

		
};
