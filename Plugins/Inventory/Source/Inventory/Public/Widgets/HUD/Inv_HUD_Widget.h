// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HUD_Widget.generated.h"


class UInv_InfoMessage;

UCLASS()
class INVENTORY_API UInv_HUD_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void ShowPickupMessage(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void HidePickupMessage();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InfoMessage> InfoMessage;
	
	UFUNCTION()
	void OnNoRoom();
};
