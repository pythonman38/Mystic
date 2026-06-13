// Midnight Madness, Inc.


#include "Widgets/Composite/Inv_LeafText.h"

#include "Components/TextBlock.h"

void UInv_LeafText::SetText(const FText& Text) const
{
	Text_LeafText->SetText(Text);
}

void UInv_LeafText::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	FSlateFontInfo FontInfo = Text_LeafText->GetFont();
	FontInfo.Size = FontSize;
	Text_LeafText->SetFont(FontInfo);
}
