// Midnight Madness, Inc.


#include "Widgets/Composite/Inv_LeafImage.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"

void UInv_LeafImage::SetImage(UTexture2D* Texture) const
{
	Image_Icon->SetBrushFromTexture(Texture);
}

void UInv_LeafImage::SetBoxSize(const FVector2D& Size) const
{
	SizeBox_Icon->SetWidthOverride(Size.X);
	SizeBox_Icon->SetHeightOverride(Size.Y);
}

void UInv_LeafImage::SetImageSize(const FVector2D& Size) const
{
	Image_Icon->SetDesiredSizeOverride(Size);
}

FVector2D UInv_LeafImage::GetImageSize() const
{
	return Image_Icon->GetDesiredSize();
}
