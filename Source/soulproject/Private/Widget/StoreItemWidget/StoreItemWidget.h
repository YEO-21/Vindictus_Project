#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreItemWidget.generated.h"

DECLARE_EVENT_OneParam(UStoreItemWidget, WeaponBuyButtonClickSignature, FName /*equipItemCode*/)


UCLASS()
class UStoreItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 무기 코드
	FName WeaponCode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Buy;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Weapon;

	// 구매 버튼 클릭 시 호출되는 이벤트
	WeaponBuyButtonClickSignature WeaponBuyEvent;


protected:
	virtual void NativeConstruct() override;


public:
	void InitializeStoreWidget(WeaponBuyButtonClickSignature weaponBuyEvent);
	


private:
	UFUNCTION()
	void OnButtonBuyClicked();
	
};
