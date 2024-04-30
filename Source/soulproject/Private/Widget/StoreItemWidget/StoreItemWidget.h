#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreItemWidget.generated.h"


UCLASS()
class UStoreItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 무기 코드
	FName WeaponCode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Buy;

	// 구매 버튼 클릭 시 호출되는 이벤트



protected:
	virtual void NativeConstruct() override;



private:
	void InitializeWeaponCode(FName weaponCode);


	
};
