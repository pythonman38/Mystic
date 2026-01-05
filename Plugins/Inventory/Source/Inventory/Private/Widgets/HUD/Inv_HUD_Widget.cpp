// Midnight Madness, Inc.


#include "Widgets/HUD/Inv_HUD_Widget.h"

#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/HUD/Inv_InfoMessage.h"

void UInv_HUD_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	auto InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->NoRoomInInventory.AddDynamic(this, &UInv_HUD_Widget::OnNoRoom);
	}
}

void UInv_HUD_Widget::OnNoRoom()
{
	if (!IsValid(InfoMessage)) return;
	InfoMessage->SetMessage(FText::FromString("No Room In Inventory!"));
}
