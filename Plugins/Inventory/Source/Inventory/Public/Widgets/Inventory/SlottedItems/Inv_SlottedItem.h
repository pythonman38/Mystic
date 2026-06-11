// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"

class UTextBlock;
class UInv_InventoryItem;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlottedItemClicked, int32, GridIndex, const FPointerEvent&, MouseEvent);

UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetImageBrush(const FSlateBrush& Brush) const;
	
	void SetInventoryItem(UInv_InventoryItem* Item);
	
	void UpdateStackCount(int32 StackCount) const;
	
	FSlottedItemClicked OnSlottedItemClicked;
	
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

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
	// Getters for private variables
	UImage* GetImage_Icon() const { return Image_Icon; }
	int32 GetGridIndex() const { return GridIndex; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	bool GetIsStackable() const { return bIsStackable; }
	
	// Setters for private variables
	void SetImage_Icon(UImage* Image) { Image_Icon = Image; }
	void SetGridIndex(int32 Index) { GridIndex = Index; }
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
	void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
};
