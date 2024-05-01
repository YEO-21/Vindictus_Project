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
	// ���� �ڵ�
	FName WeaponCode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Buy;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Weapon;

	// ���� ��ư Ŭ�� �� ȣ��Ǵ� �̺�Ʈ
	WeaponBuyButtonClickSignature WeaponBuyEvent;


protected:
	virtual void NativeConstruct() override;


public:
	void InitializeStoreWidget(WeaponBuyButtonClickSignature weaponBuyEvent);
	


private:
	UFUNCTION()
	void OnButtonBuyClicked();
	
};
