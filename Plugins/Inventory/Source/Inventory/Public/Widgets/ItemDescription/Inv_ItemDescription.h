// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_ItemDescription.generated.h"


class USizeBox;

UCLASS()
class INVENTORY_API UInv_ItemDescription : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FVector2D GetBoxSize() const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
};
