// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Items/Manifest/ItemManifest.h"
#include "UObject/Object.h"
#include "Inv_InventoryItem.generated.h"


UCLASS()
class INVENTORY_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	void SetItemManifest(const FInv_ItemManifest& Manifest);

	bool IsStackable() const;
	
private:
	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/Inventory.Inv_ItemManifest"), Replicated)
	FInstancedStruct ItemManifest;
	
	UPROPERTY(Replicated)
	int32 TotalStackCount{0};
	
public:
	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); }
	FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); }
	int32 GetTotalStackCount() const { return TotalStackCount; }
	
	void SetTotalStackCount(int32 Count) { TotalStackCount = Count; }
};

template <typename FragmentType>
const FragmentType* GetFragment(const UInv_InventoryItem* Item, const FGameplayTag& Tag)
{
	if (!IsValid(Item)) return nullptr;
	
	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	return Manifest.GetFragmentOfTypeWithTag<FragmentType>(Tag);
}
