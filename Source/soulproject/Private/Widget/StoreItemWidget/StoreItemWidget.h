#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreItemWidget.generated.h"


UCLASS()
class UStoreItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ���� �ڵ�
	FName WeaponCode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Buy;

	// ���� ��ư Ŭ�� �� ȣ��Ǵ� �̺�Ʈ



protected:
	virtual void NativeConstruct() override;



private:
	void InitializeWeaponCode(FName weaponCode);


	
};
