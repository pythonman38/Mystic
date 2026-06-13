// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Inv_Leaf.h"
#include "Inv_LeafText.generated.h"


class UTextBlock;

UCLASS()
class INVENTORY_API UInv_LeafText : public UInv_Leaf
{
	GENERATED_BODY()
	
public:
	void SetText(const FText& Text) const;
	
protected:
	virtual void NativePreConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_LeafText;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 FontSize{12};
};
