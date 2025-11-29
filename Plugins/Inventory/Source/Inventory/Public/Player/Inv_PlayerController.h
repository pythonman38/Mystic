// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"


class UInv_InventoryComponent;
class UInv_HUD_Widget;
class UInputMappingContext;
class UInputAction;

UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController
{
public:
	AInv_PlayerController();

	virtual void Tick(float DeltaTime) override;

private:
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

private:
	void PrimaryInteract();

	void CreateHUD_Widget();

	void TraceForItem();
	
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TSubclassOf<UInv_HUD_Widget> HUD_WidgetClass;

	UPROPERTY()
	TObjectPtr<UInv_HUD_Widget> HUD_Widget;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	double TraceLength;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	TWeakObjectPtr<AActor> ThisActor, LastActor;

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
};
