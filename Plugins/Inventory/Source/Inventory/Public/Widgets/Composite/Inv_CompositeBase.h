// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inv_CompositeBase.generated.h"

UCLASS()
class INVENTORY_API UInv_CompositeBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Collapse();
	
	void Expand();
	
	using FuncType = TFunction<void(UInv_CompositeBase*)>;
	
	virtual void ApplyFunction(FuncType Function) {}
	
private:
	UPROPERTY(EditAnywhere, Category = Inventory)
	FGameplayTag FragmentTag;

public:
	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	
	virtual void SetFragmentTag(FGameplayTag Tag) { FragmentTag = Tag; }
};
