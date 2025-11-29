// Midnight Madness, Inc.


#include "InventoryManagement/Components/Inv_InventoryComponent.h"

#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"


UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	bInventoryMenuOpen ? HandleToggleInventoryMenu(ESlateVisibility::Collapsed, false) : HandleToggleInventoryMenu(ESlateVisibility::Visible, true);
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
