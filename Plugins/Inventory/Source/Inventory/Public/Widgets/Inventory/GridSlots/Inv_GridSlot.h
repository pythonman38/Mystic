// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

class UInv_InventoryItem;
class UImage;

UENUM(BlueprintType)
enum class EInv_GridSlotState : uint8
{
	Unoccupied,
	Occupied,
	Selected,
	GrayedOut
};

UCLASS()
class INVENTORY_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetOccupiedTexture();
	
	void SetUnoccupiedTexture();
	
	void SetSelectedTexture();
	
	void SetGrayedOutTexture();
	
	void SetInventoryItem(UInv_InventoryItem* Item);

private:
	bool bAvailable;
	
	int32 TileIndex, StackCount, UpperLeftIndex{INDEX_NONE};
	
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_GridSlot;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	FSlateBrush Brush_Unoccupied;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	FSlateBrush Brush_Occupied;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	FSlateBrush Brush_Selected;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	FSlateBrush Brush_GrayedOut;
	
	EInv_GridSlotState GridSlotState;
	
public:
	bool IsAvailable() const { return bAvailable; }
	int32 GetTileIndex() const { return TileIndex; }
	int32 GetStackCount() const { return StackCount; }
	int32 GetUpperLeftIndex() const { return UpperLeftIndex; }
	EInv_GridSlotState GetGridSlotState() const { return GridSlotState; }
	TWeakObjectPtr<UInv_InventoryItem> GetInventoryItem() const { return InventoryItem; }
	
	void SetAvailable(bool bIsAvailable) { bAvailable = bIsAvailable; }
	void SetTileIndex(int32 NewIndex) { TileIndex = NewIndex; }
	void SetStackCount(int32 NewCount) { StackCount = NewCount; }
	void SetUpperLeftIndex(int32 NewIndex) { UpperLeftIndex = NewIndex; }
	void SetGridSlotState(EInv_GridSlotState NewState) { GridSlotState = NewState; }
};
