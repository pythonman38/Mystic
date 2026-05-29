// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/Inv_FastArray.h"
#include "Inv_InventoryComponent.generated.h"


class UInv_ItemComponent;
class UInv_InventoryItem;
class UInv_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChange, UInv_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStackChange, const FInv_SlotAvailabilityResult&, Result);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_InventoryComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	void TryAddItem(UInv_ItemComponent* ItemComponent);
	
	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UInv_ItemComponent* ItemComponent, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStackToItem(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);

	void ToggleInventoryMenu();
	
	void AddRepSubObj(UObject* SubObj);
	
	FOnInventoryItemChange OnItemAdded;
	FOnInventoryItemChange OnItemRemoved;
	FNoRoomInInventory NoRoomInInventory;
	FStackChange OnStackChange;

protected:
	virtual void BeginPlay() override;

private:
	void ConstructInventory();
	
	UPROPERTY(Replicated)
	FInv_InventoryFastArray InventoryList;

	void HandleToggleInventoryMenu(ESlateVisibility Visibility, bool bIsOpen);
	
	TWeakObjectPtr<APlayerController> OwningController;

	UPROPERTY()
	TObjectPtr<UInv_InventoryBase> InventoryMenu;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInv_InventoryBase> InventoryMenuClass;

	bool bInventoryMenuOpen;
};
