// Midnight Madness, Inc.


#include "Widgets/ItemDescription/Inv_ItemDescription.h"

#include "Components/SizeBox.h"

FVector2D UInv_ItemDescription::GetBoxSize() const
{
	return SizeBox->GetDesiredSize();
}
