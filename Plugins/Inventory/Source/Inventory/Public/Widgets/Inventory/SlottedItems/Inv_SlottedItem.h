// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"

class UTextBlock;
class UInv_InventoryItem;
class UImage;

UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetImageBrush(const FSlateBrush& Brush) const;
	
	void SetInventoryItem(UInv_InventoryItem* Item);
	
	void UpdateStackCount(int32 StackCount);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;

	int32 GridIndex;

	FIntPoint GridDimensions;

	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;

	bool bIsStackable{false};
	
public:
	// Setters for private variables
	void SetImage_Icon(UImage* Image) { Image_Icon = Image; }
	void SetGridIndex(int32 Index) { GridIndex = Index; }
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
	void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }

	// Getters for private variables
	UImage* GetImage_Icon() const { return Image_Icon; }
	int32 GetGridIndex() const { return GridIndex; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	bool GetIsStackable() const { return bIsStackable; }
};
