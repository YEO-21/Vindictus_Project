#pragma once

#include "CoreMinimal.h"
#include "Actor/NpcCharacter/NpcCharacter.h"
#include "NpcWalldo.generated.h"




UCLASS()
class ANpcWalldo : public ANpcCharacter
{
	GENERATED_BODY()


// 판매 아이템 코드가 정의되어있는 DataTableAsset

private:
	TSubclassOf<class UWeaponStoreWidget> BP_WeaponStoreWidgetClass;

	TSubclassOf<class UStoreItemWidget> ItemWidgetClass;

	class UDataTable* DT_SaleItem;

protected:
	// Walldo의 무기 상점 위젯 객체
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
