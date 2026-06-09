// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_ItemPopUp.generated.h"

class USizeBox;
class UTextBlock;
class UButton;
class USlider;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FPopUpMenuSplit, int32, SplitAmount, int32, Index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPopUpMenuDrop, int32, Index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPopUpMenuConsume, int32, Index);

UCLASS()
class INVENTORY_API UInv_ItemPopUp : public UUserWidget
{
	GENERATED_BODY()
	
public:
	int32 GetSplitAmount() const;
	
	void CollapseSplitButton() const;
	
	void CollapseConsumeButton() const;
	
	void SetSliderParams(const float Max, const float Value) const;
	
	FVector2D GetBoxSize() const;
	
	FPopUpMenuSplit OnSplit;
	FPopUpMenuDrop OnDrop;
	FPopUpMenuConsume OnConsume;
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
private:
	UFUNCTION()
	void SplitButtonClicked();
	
	UFUNCTION()
	void DropButtonClicked();
	
	UFUNCTION()
	void ConsumeButtonClicked();
	
	UFUNCTION()
	void SliderValueChanged(float Value);
	
	int32 GridIndex{INDEX_NONE};
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Split;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Drop;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Consume;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> Slider_Split;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_SplitAmount;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
	
public:
	int32 GetGridIndex() const { return GridIndex; }
	void SetGridIndex(int32 Index) { GridIndex = Index; }
};
