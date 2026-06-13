// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Inv_CompositeBase.h"
#include "Inv_Composite.generated.h"


UCLASS()
class INVENTORY_API UInv_Composite : public UInv_CompositeBase
{
	GENERATED_BODY()
	
public:
	virtual void ApplyFunction(FuncType Function) override;
	
	virtual void Collapse() override;
	
protected:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UInv_CompositeBase>> Children;
};
