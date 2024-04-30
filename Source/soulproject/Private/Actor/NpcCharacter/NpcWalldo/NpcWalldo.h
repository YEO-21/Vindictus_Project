#pragma once

#include "CoreMinimal.h"
#include "Actor/NpcCharacter/NpcCharacter.h"
#include "NpcWalldo.generated.h"




UCLASS()
class ANpcWalldo : public ANpcCharacter
{
	GENERATED_BODY()



private:
	TSubclassOf<class UWeaponStoreWidget> BP_WeaponStoreWidgetClass;

	TSubclassOf<class UStoreItemWidget> ItemWidgetClass;

protected:
	// WalldoÀÇ ¹«±â »óÁ¡ À§Á¬ °´Ã¼
	UPROPERTY()
	class UWeaponStoreWidget* NpcWeaponStoreWidget;


public :
	ANpcWalldo();

	virtual bool OnInteractionStarted(FOnInteractionFinishSignature onInteractionFinished) override;
	
	virtual class UInteractionParamBase* GetInteractionParam() override;

private:
	UFUNCTION()
	FName GetWeaponCode();

protected:
	virtual void BeginPlay() override;

	virtual void CheckTradable() override;






	
};
