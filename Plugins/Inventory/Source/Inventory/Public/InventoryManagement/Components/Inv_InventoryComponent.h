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
	
	virtual void BeginPlay() override;
	
	void ToggleInventoryMenu();
	
	void AddRepSubObj(UObject* SubObj);
	
	void SpawnDroppedItem(UInv_InventoryItem* Item, int32 StackCount) const;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Inventory)
	void TryAddItem(UInv_ItemComponent* ItemComponent);
	
	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UInv_ItemComponent* ItemComponent, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStackToItem(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	
	UFUNCTION(Server, Reliable)
	void Server_DropItem(UInv_InventoryItem* Item, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_ConsumeItem(UInv_InventoryItem* Item);
	
	FOnInventoryItemChange OnItemAdded;
	FOnInventoryItemChange OnItemRemoved;
	FNoRoomInInventory NoRoomInInventory;
	FStackChange OnStackChange;

private:
	void ConstructInventory();
	
	void HandleToggleInventoryMenu(ESlateVisibility Visibility, bool bIsOpen);
	
	bool bInventoryMenuOpen;
	
	TWeakObjectPtr<APlayerController> OwningController;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	float DropSpawningAngleMin{-85.f};
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	float DropSpawningAngleMax{85.f};
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	float DropSpawnDistanceMin{10.f};
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	float DropSpawnDistanceMax{50.f};
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	float RelativeSpawnElevation{-70.f};
	
	UPROPERTY(Replicated)
	FInv_InventoryFastArray InventoryList;

	UPROPERTY()
	TObjectPtr<UInv_InventoryBase> InventoryMenu;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInv_InventoryBase> InventoryMenuClass;

	
};
