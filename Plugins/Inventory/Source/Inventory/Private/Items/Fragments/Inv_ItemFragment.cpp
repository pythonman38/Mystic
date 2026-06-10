#include "Items/Fragments/Inv_ItemFragment.h"

void FInv_HealthPotionFragment::OnConsume(APlayerController* PC)
{
	const FString Message = FString::Printf(TEXT("Health Potion consumed! Healing by: %f!"), HealAmount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
}

void FInv_ManaPotionFragment::OnConsume(APlayerController* PC)
{
	const FString Message = FString::Printf(TEXT("Mana Potion consumed! Mana replenished by: %f!"), ManaAmount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message);
}
