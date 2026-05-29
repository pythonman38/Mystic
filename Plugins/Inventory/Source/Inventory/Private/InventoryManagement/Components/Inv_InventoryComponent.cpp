// Midnight Madness, Inc.


#include "InventoryManagement/Components/Inv_InventoryComponent.h"

#include "Items/Components/Inv_ItemComponent.h"
#include "Items/Inv_InventoryItem.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"


UInv_InventoryComponent::UInv_InventoryComponent() : InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	bInventoryMenuOpen = false;
}

void UInv_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, InventoryList);
}

void UInv_InventoryComponent::TryAddItem(UInv_ItemComponent* ItemComponent)
{
	FInv_SlotAvailabilityResult Result = InventoryMenu->HasRoomForItem(ItemComponent);
	UInv_InventoryItem* FoundItem = InventoryList.FindFirstItemByType(ItemComponent->GetItemManifest().GetItemType());
	Result.Item = FoundItem;
	if (Result.TotalRoomToFill == 0)
	{
		NoRoomInInventory.Broadcast();
		return;
	}
	
	if (Result.Item.IsValid() && Result.bStackable)
	{
		// Add stacks to an item that already exists in the inventory. We only want to update the stack count, not create an item.
		Server_AddStackToItem(ItemComponent, Result.TotalRoomToFill, Result.Remainder);
	}
	else if (Result.TotalRoomToFill > 0)
	{
		// This item type doesn't exist in the inventory. Create a new one and update all pertinent slots.
		Server_AddNewItem(ItemComponent, Result.bStackable ? Result.TotalRoomToFill : 0);
	}
}

void UInv_InventoryComponent::Server_AddNewItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount)
{
	auto NewItem = InventoryList.AddEntry(ItemComponent);
	if (GetOwner()->GetNetMode() == NM_ListenServer || GetOwner()->GetNetMode() == NM_Standalone)
	{
		OnItemAdded.Broadcast(NewItem);
	}
	
	// TODO: Tell the item component to destroy its owning actor.
}

void UInv_InventoryComponent::Server_AddStackToItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder)
{
	
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	bInventoryMenuOpen ? HandleToggleInventoryMenu(ESlateVisibility::Collapsed, false) : HandleToggleInventoryMenu(ESlateVisibility::Visible, true);
}

void UInv_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(SubObj)) AddReplicatedSubObject(SubObj);
}


void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ConstructInventory();
}

void UInv_InventoryComponent::ConstructInventory()
{
	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("Inventory Component should have a Player Controller as Owner!"));
	if (!OwningController->IsLocalController()) return;
	InventoryMenu = CreateWidget<UInv_InventoryBase>(OwningController.Get(), InventoryMenuClass);
	InventoryMenu->AddToViewport();
	HandleToggleInventoryMenu(ESlateVisibility::Collapsed, false);
}

void UInv_InventoryComponent::HandleToggleInventoryMenu(ESlateVisibility Visibility, bool bIsOpen)
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetVisibility(Visibility);
	bInventoryMenuOpen = bIsOpen;
	if (!OwningController.IsValid()) return;
	FInputModeGameAndUI GameAndUI;
	FInputModeGameOnly GameOnly;
	bIsOpen ? OwningController->SetInputMode(GameAndUI) : OwningController->SetInputMode(GameOnly);
	OwningController->SetShowMouseCursor(bIsOpen);
}
