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
		OnStackChange.Broadcast(Result);
		Server_AddStackToItem(ItemComponent, Result.TotalRoomToFill, Result.Remainder);
	}
	else if (Result.TotalRoomToFill > 0)
	{
		// This item type doesn't exist in the inventory. Create a new one and update all pertinent slots.
		Server_AddNewItem(ItemComponent, Result.bStackable ? Result.TotalRoomToFill : 0);
	}
}

void UInv_InventoryComponent::Server_ConsumeItem_Implementation(UInv_InventoryItem* Item)
{
	const int32 NewStackCount = Item->GetTotalStackCount() - 1;
	NewStackCount <= 0 ? InventoryList.RemoveEntry(Item) : Item->SetTotalStackCount(NewStackCount);
	// Get the Consumable Fragment and call Consume()
	if (auto ConsumableFragment = Item->GetItemManifestMutable().GetFragmentOfTypeMutable<FInv_ConsumableFragment>()) ConsumableFragment->OnConsume(OwningController.Get());
}

void UInv_InventoryComponent::Server_AddNewItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount)
{
	auto NewItem = InventoryList.AddEntry(ItemComponent);
	NewItem->SetTotalStackCount(StackCount);
	if (GetOwner()->GetNetMode() == NM_ListenServer || GetOwner()->GetNetMode() == NM_Standalone)
	{
		OnItemAdded.Broadcast(NewItem);
	}
	
	ItemComponent->PickedUp();
}

void UInv_InventoryComponent::Server_AddStackToItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder)
{
	const FGameplayTag& ItemType = IsValid(ItemComponent) ? ItemComponent->GetItemManifest().GetItemType() : FGameplayTag::EmptyTag;
	UInv_InventoryItem* Item = InventoryList.FindFirstItemByType(ItemType);
	if (!IsValid(Item)) return;
	
	Item->SetTotalStackCount(Item->GetTotalStackCount() + StackCount);
	
	if (Remainder == 0) ItemComponent->PickedUp();
	else if (FInv_StackableFragment* StackableFragment = ItemComponent->GetItemManifest().GetFragmentOfTypeMutable<FInv_StackableFragment>())
	{
		StackableFragment->SetStackCount(Remainder);
	}
}

void UInv_InventoryComponent::Server_DropItem_Implementation(UInv_InventoryItem* Item, int32 StackCount)
{
	const int32 NewStackCount = Item->GetTotalStackCount() - StackCount;
	(NewStackCount <= 0) ? InventoryList.RemoveEntry(Item) : Item->SetTotalStackCount(NewStackCount);
	SpawnDroppedItem(Item, StackCount);
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	bInventoryMenuOpen ? HandleToggleInventoryMenu(ESlateVisibility::Collapsed, false) : HandleToggleInventoryMenu(ESlateVisibility::Visible, true);
}

void UInv_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(SubObj)) AddReplicatedSubObject(SubObj);
}

void UInv_InventoryComponent::SpawnDroppedItem(UInv_InventoryItem* Item, int32 StackCount) const
{
	// Spawn the dropped item in the level
	const APawn* OwningPawn = OwningController->GetPawn();
	FVector RotatedForward = OwningPawn->GetActorForwardVector();
	RotatedForward = RotatedForward.RotateAngleAxis(FMath::FRandRange(DropSpawningAngleMin, DropSpawningAngleMax), FVector::UpVector);
	FVector SpawnLocation = OwningPawn->GetActorLocation() + RotatedForward * FMath::FRandRange(DropSpawnDistanceMin, DropSpawnDistanceMax);
	SpawnLocation.Z += RelativeSpawnElevation;
	const FRotator SpawnRotation = FRotator::ZeroRotator;
	// Have the Item Manifest spawn the pickup actor
	FInv_ItemManifest& ItemManifest = Item->GetItemManifestMutable();
	if (auto StackableFragment = ItemManifest.GetFragmentOfTypeMutable<FInv_StackableFragment>()) StackableFragment->SetStackCount(StackCount);
	ItemManifest.SpawnPickupActor(this, SpawnLocation, SpawnRotation);
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
