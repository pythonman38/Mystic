// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HoverItem.generated.h"

/**
 * The HoverItem is teh item that will appear and follow the mouse
 * when an inventory item on the grid has been clicked.
 */

class UTextBlock;
class UInv_InventoryItem;
class UImage;

UCLASS()
class INVENTORY_API UInv_HoverItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetImageBrush(const FSlateBrush& Brush) const;
	
	void UpdateStackCount(const int32 Count) const;
	
	FGameplayTag GetItemType() const;
	
	void SetIsStackable(bool bStacks);
	
	UInv_InventoryItem* GetInventoryItem() const;
	
	void SetInventoryItem(UInv_InventoryItem* Item);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;
	
	int32 PreviousGridIndex;
	
	FIntPoint GridDimensions;
	
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	
	bool bIsStackable{false};
	
	int32 StackCount{0};
	
public:
	int32 GetStackCount() const { return StackCount; }
	int32 GetPreviousGridIndex() const { return PreviousGridIndex; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }
	bool IsStackable() const { return bIsStackable; }
	
	void SetPreviousGridIndex(int32 Index) { PreviousGridIndex = Index; }
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
};
