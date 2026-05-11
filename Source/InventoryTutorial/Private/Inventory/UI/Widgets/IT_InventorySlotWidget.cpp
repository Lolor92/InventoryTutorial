#include "Inventory/UI/Widgets/IT_InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/Component/IT_InventoryComponent.h"
#include "Inventory/Component/IT_InventoryUIManager.h"
#include "Inventory/Replication/IT_InventoryFastArray.h"


void UIT_InventorySlotWidget::InitSlotWidget(UIT_InventoryUIManager* InInventoryUIManager,
                                             const FGameplayTag& InContainerId,int32 InSlotIndex)
{
	InventoryUIManager = InInventoryUIManager;
	ContainerId = InContainerId;
	SlotIndex = InSlotIndex;
	
	Refresh();
}

void UIT_InventorySlotWidget::Refresh()
{
	auto InventoryComponent = InventoryUIManager->GetInventoryComponent();
	if (!InventoryComponent)
	{
		SetToDefault();
		return;
	}
	
	const FInventoryEntry* Entry = InventoryComponent->FindEntryAtSlot(ContainerId, SlotIndex);
	if (!Entry)
	{
		SetToDefault();
		return;
	}
	
	FGameplayTag ItemTag = Entry->ItemTag;
	if (!ItemTag.IsValid())
	{
		SetToDefault();
		return;
	}
	
	const UIT_ItemDatabase* ItemDatabase = InventoryComponent->GetItemDatabase();
	const UIT_ItemDefinition* Def = ItemDatabase ? ItemDatabase->GetItemDefinitionByTag(ItemTag) : nullptr;
	if (!Def)
	{
		SetToDefault();
		return;
	}
	
	if (SlotBackgroundImage)
	{
		SlotBackgroundImage->SetBrush(GetBackgroundRarityBrush(Def->ItemRarity));
	}
	
	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemIcon->SetBrushFromTexture(Def->ItemIcon);
	}
	
	if (QuantityText)
	{
		QuantityText->SetVisibility(Def->bStackable ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
		QuantityText->SetText(Def->bStackable ? FText::AsNumber(Entry->Quantity) : FText::GetEmpty());
	}
	
	if (HoverImage)
	{
		HoverImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UIT_InventorySlotWidget::SetToDefault()
{
	if (SlotBackgroundImage)
	{
		SlotBackgroundImage->SetBrush(DefaultSlotBackgroundBrush);
	}
	
	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		ItemIcon->SetBrushFromTexture(nullptr);
	}
	
	if (QuantityText)
	{
		QuantityText->SetVisibility(ESlateVisibility::Hidden);
		QuantityText->SetText(FText::GetEmpty());
	}
	
	if (HoverImage)
	{
		HoverImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

const FSlateBrush& UIT_InventorySlotWidget::GetBackgroundRarityBrush(EItemRarity Rarity) const
{
	switch (Rarity)
	{
		case EItemRarity::Common:
		return CommonSlotBackgroundBrush;
		
		case EItemRarity::Rare:
		return RareSlotBackgroundBrush;
		
		case EItemRarity::Epic:
		return EpicSlotBackgroundBrush;
		
		case EItemRarity::Legendary:
		return LegendarySlotBackgroundBrush;
		
		default:
		return DefaultSlotBackgroundBrush;
	}
}
