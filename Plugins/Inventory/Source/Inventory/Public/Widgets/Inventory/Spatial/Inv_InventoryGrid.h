// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"


class UInv_HoverItem;
struct FGameplayTag;
struct FInv_ImageFragment;
struct FInv_GridFragment;
class UInv_SlottedItem;
struct FInv_ItemManifest;
class UInv_ItemComponent;
class UInv_InventoryComponent;
class UCanvasPanel;
class UInv_GridSlot;

UCLASS()
class INVENTORY_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	EInv_ItemCategory GetItemCategory() const { return ItemCategory; }

	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_ItemComponent* ItemComponent);

	UFUNCTION()
	void AddItem(UInv_InventoryItem* Item);
	
protected:
	virtual void NativeOnInitialized() override;
	
private:
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;

	void ConstructGrid();

	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_InventoryItem* Item);

	FInv_SlotAvailabilityResult HasRoomForItem(const FInv_ItemManifest& Manifest);

	void AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem);

	bool MatchesCategory(const UInv_InventoryItem* Item) const;

	FVector2D GetDrawSize(const FInv_GridFragment* GridFragment) const;

	void SetSlottedItemImage(const UInv_SlottedItem* SlottedItem, const FInv_GridFragment* GridFragment,
	                         const FInv_ImageFragment* ImageFragment) const;

	void AddItemAtIndex(UInv_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount);
	
	void AddSlottedItemToCanvas(const int32 Index, const FInv_GridFragment* GridFragment, UInv_SlottedItem* SlottedItem) const;

	UInv_SlottedItem* CreateSlottedItem(UInv_InventoryItem* Item, const bool bStackable, const int32 StackAmount,
		const FInv_GridFragment* GridFragment, const FInv_ImageFragment* ImageFragment,const int32 Index);
	
	void UpdateGridSlots(UInv_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount);

	static bool IsIndexClaimed(const TSet<int32>& CheckedIndices, const int32 Index);
	
	bool HasRoomAtIndex(const UInv_GridSlot* GridSlot, const FIntPoint& Dimensions, const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed,
		const FGameplayTag& ItemType, const int32 MaxStackSize);

	static FIntPoint GetItemDimensions(const FInv_ItemManifest& Manifest);

	static bool CheckSlotConstraints(const UInv_GridSlot* GridSlot, const UInv_GridSlot* SubGridSlot, const TSet<int32>& CheckedIndices, 
	                                 TSet<int32>& OutTentativelyClaimed, const FGameplayTag& ItemType, const int32 MaxStackSize);

	static bool HasValidItem(const UInv_GridSlot* GridSlot);

	static bool IsUpperLeftSlot(const UInv_GridSlot* GridSlot, const UInv_GridSlot* SubGridSlot);

	static bool DoesItemTypeMatch(const UInv_InventoryItem* SubItem, const FGameplayTag& ItemType);
	
	bool IsInGridBounds(const int32 StartIndex, const FIntPoint& ItemDimensions) const;
	
	int32 DetermineFillAmountForSlot(const bool bStackable, const int32 MaxStackSize, const int32 AmountToFill, const UInv_GridSlot* GridSlot) const;
	
	int32 GetStackAmount(const UInv_GridSlot* GridSlot) const;

	static bool IsRightClick(const FPointerEvent& MouseEvent);

	static bool IsLeftClick(const FPointerEvent& MouseEvent);
	
	void PickUp(UInv_InventoryItem* ClickedInventoryItem, const int32 GridIndex);
	
	void AssignHoverItem(UInv_InventoryItem* InventoryItem);
	
	void AssignHoverItem(UInv_InventoryItem* InventoryItem, const int32 GridIndex, const int32 PreviousGridIndex);
	
	void RemoveItemFromGrid(UInv_InventoryItem* InventoryItem, const int32 GridIndex);
	
	UFUNCTION()
	void AddStacks(const FInv_SlotAvailabilityResult& Result);
	
	UFUNCTION()
	void OnSlottedItemClicked(int32 GridIndex, const FPointerEvent& MouseEvent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = true))
	EInv_ItemCategory ItemCategory;

	UPROPERTY()
	TArray<TObjectPtr<UInv_GridSlot>> GridSlots;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInv_GridSlot> GridSlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInv_SlottedItem> SlottedItemClass;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<UInv_SlottedItem>> SlottedItems;

	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 Rows;

	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 Columns;

	UPROPERTY(EditAnywhere, Category = Inventory)
	float TileSize;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInv_HoverItem> HoverItemClass;
	
	UPROPERTY()
	TObjectPtr<UInv_HoverItem> HoverItem;
};
