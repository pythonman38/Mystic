// Midnight Madness, Inc.


#include "Widgets/Composite/Inv_Composite.h"

#include "Blueprint/WidgetTree.h"

void UInv_Composite::ApplyFunction(FuncType Function)
{
	for (auto& Child : Children) Child->ApplyFunction(Function);
}

void UInv_Composite::Collapse()
{
	for (auto& Child : Children) Child->Collapse();
}

void UInv_Composite::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		UInv_CompositeBase* Composite = Cast<UInv_CompositeBase>(Widget);
		if (IsValid(Composite))
		{
			Children.Add(Composite);
			Composite->Collapse();
		}
	});
}
