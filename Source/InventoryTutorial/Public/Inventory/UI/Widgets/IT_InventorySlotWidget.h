#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/Types/Item/IT_ItemTypes.h"
#include "IT_InventorySlotWidget.generated.h"


class UIT_InventoryUIManager;
class UImage;
class UTextBlock;

UCLASS()
class INVENTORYTUTORIAL_API UIT_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSlotWidget(UIT_InventoryUIManager* InInventoryUIManager, const FGameplayTag& InContainerId ,int32 InSlotIndex);
	
	void Refresh();
	void SetToDefault();
	
	UFUNCTION(BlueprintPure, Category = "Inventory|UI")
	int32 GetSlotIndex() const { return SlotIndex; }
	
	const FSlateBrush& GetBackgroundRarityBrush(EItemRarity Rarity) const;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UIT_InventoryUIManager> InventoryUIManager = nullptr;
	
	UPROPERTY(Transient)
	FGameplayTag ContainerId;
	
	UPROPERTY(Transient)
	int32 SlotIndex = INDEX_NONE;
	
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UImage> SlotBackgroundImage = nullptr;
	
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UImage> ItemIcon = nullptr;
	
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> QuantityText = nullptr;
	
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UImage> HoverImage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|UI|Rarity")
	FSlateBrush DefaultSlotBackgroundBrush;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|UI|Rarity")
	FSlateBrush CommonSlotBackgroundBrush;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|UI|Rarity")
	FSlateBrush RareSlotBackgroundBrush;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|UI|Rarity")
	FSlateBrush EpicSlotBackgroundBrush;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory|UI|Rarity")
	FSlateBrush LegendarySlotBackgroundBrush;
};
