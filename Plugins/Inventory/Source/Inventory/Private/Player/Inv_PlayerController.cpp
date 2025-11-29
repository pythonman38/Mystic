// Midnight Madness, Inc.


#include "Player/Inv_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/Inv_Highlightable.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/Inv_HUD_Widget.h"

AInv_PlayerController::AInv_PlayerController() :
TraceLength(500.0),
ItemTraceChannel(ECC_GameTraceChannel1)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForItem();
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		for (auto CurrentContext : DefaultIMCs)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}

	InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();

	CreateHUD_Widget();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AInv_PlayerController::PrimaryInteract);
	EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AInv_PlayerController::ToggleInventory);
}

void AInv_PlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();
}

void AInv_PlayerController::PrimaryInteract()
{
	UE_LOG(LogTemp, Log, TEXT("Primary Interact"));
}

void AInv_PlayerController::CreateHUD_Widget()
{
	if (!IsLocalPlayerController()) return;

	HUD_Widget = CreateWidget<UInv_HUD_Widget>(this, HUD_WidgetClass);
	if (IsValid(HUD_Widget)) HUD_Widget->AddToViewport();
}

void AInv_PlayerController::TraceForItem()
{
	if (IsValid(GEngine) && IsValid(GEngine->GameViewport))
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter = ViewportSize / 2.0f;
		FVector TraceStart, Forward;
		if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;
		FVector TraceEnd = TraceStart + Forward * TraceLength;
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);
		LastActor = ThisActor;
		ThisActor = HitResult.GetActor();
		if (!ThisActor.IsValid()) if (IsValid(HUD_Widget)) HUD_Widget->HidePickupMessage();
		if (ThisActor == LastActor) return;
		if (ThisActor.IsValid())
		{
			if (auto Highlightable = ThisActor->FindComponentByInterface(UInv_Highlightable::StaticClass()); IsValid(Highlightable))
			{
				IInv_Highlightable::Execute_Highlight(Highlightable);
			}
			if  (auto ItemComponent = ThisActor->FindComponentByClass<UInv_ItemComponent>())
			{
				if (IsValid(HUD_Widget)) HUD_Widget->ShowPickupMessage(ItemComponent->GetPickupMessage());
			}
		}
		if (LastActor.IsValid())
		{
			if (auto Highlightable = LastActor->FindComponentByInterface(UInv_Highlightable::StaticClass()); IsValid(Highlightable))
			{
				IInv_Highlightable::Execute_UnHighlight(Highlightable);
			}
		}
	}
	
}


