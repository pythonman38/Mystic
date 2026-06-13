// Midnight Madness, Inc.


#include "Widgets/Composite/Inv_LeafLabeledValue.h"

#include "Components/TextBlock.h"

void UInv_LeafLabeledValue::SetTextLabel(const FText& Text, bool bCollapse) const
{
	if (bCollapse)
	{
		Text_Label->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	Text_Label->SetText(Text);
}

void UInv_LeafLabeledValue::SetTextValue(const FText& Text, bool bCollapse) const
{
	if (bCollapse)
	{
		Text_Value->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	Text_Value->SetText(Text);
}

void UInv_LeafLabeledValue::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	FSlateFontInfo FontInfoLabel = Text_Label->GetFont();
	FontInfoLabel.Size = FontSize_Label;
	Text_Label->SetFont(FontInfoLabel);
	
	FSlateFontInfo FontInfoValue = Text_Value->GetFont();
	FontInfoValue.Size = FontSize_Value;
	Text_Value->SetFont(FontInfoValue);
}
