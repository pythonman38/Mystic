// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/ItemManifest.h"
#include "Inv_ItemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_ItemComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FInv_ItemManifest& GetItemManifest() { return ItemManifest; }

	FString GetPickupMessage() const { return PickupMessage; }

private:
	UPROPERTY(Replicated, EditAnywhere, Category = Inventory)
	FInv_ItemManifest ItemManifest;
	
	UPROPERTY(EditAnywhere, Category = Inventory)
	FString PickupMessage;
};
