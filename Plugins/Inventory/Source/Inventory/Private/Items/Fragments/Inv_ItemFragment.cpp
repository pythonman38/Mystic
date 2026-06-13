#include "Items/Fragments/Inv_ItemFragment.h"

#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Widgets/Composite/Inv_LeafImage.h"
#include "Widgets/Composite/Inv_LeafLabeledValue.h"
#include "Widgets/Composite/Inv_LeafText.h"

void FInv_InventoryItemFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	if (MatchesWidgetTag(Composite)) Composite->Expand();
}

bool FInv_InventoryItemFragment::MatchesWidgetTag(const UInv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}

void FInv_ImageFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;
	
	if (auto Image = Cast<UInv_LeafImage>(Composite))
	{
		Image->SetImage(Icon);
		Image->SetBoxSize(IconDimensions);
		Image->SetImageSize(IconDimensions);
	}
}

void FInv_TextFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;
	
	if (auto LeafText = Cast<UInv_LeafText>(Composite))
	{
		LeafText->SetText(FragmentText);
	}
}

void FInv_LabeledNumberFragment::Manifest()
{
	if (bRandomizeOnManifest) Value = FMath::FRandRange(Min, Max);
	bRandomizeOnManifest = false;
}

void FInv_LabeledNumberFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	auto LabeledValue = Cast<UInv_LeafLabeledValue>(Composite);
	if (MatchesWidgetTag(Composite) && IsValid(LabeledValue))
	{
		LabeledValue->SetTextLabel(Text_Label, bCollapsedLabel);
		FNumberFormattingOptions Options;
		Options.MinimumFractionalDigits = MinFractionalDigits;
		Options.MaximumFractionalDigits = MaxFractionalDigits;
		LabeledValue->SetTextValue(FText::AsNumber(Value, &Options), bCollapsedValue);
	}
}

void FInv_ConsumableFragment::OnConsume(APlayerController* PC)
{
	for (auto& Modifier : ConsumeModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.OnConsume(PC);
	}
}

void FInv_ConsumableFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	for (const auto& Modifier : ConsumeModifiers)
	{
		const auto& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

void FInv_ConsumableFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	
	for (auto& Modifier : ConsumeModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

void FInv_HealthPotionFragment::OnConsume(APlayerController* PC)
{
	const FString Message = FString::Printf(TEXT("Health Potion consumed! Healing by: %f!"), GetValue());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
}

void FInv_ManaPotionFragment::OnConsume(APlayerController* PC)
{
	const FString Message = FString::Printf(TEXT("Mana Potion consumed! Mana replenished by: %f!"), GetValue());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message);
}
