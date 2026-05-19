#include "Inventory/UI/Widgets/IT_WidgetBase.h"
#include "Inventory/Component/IT_InventoryUIManager.h"

void UIT_WidgetBase::InitWidget(UIT_InventoryUIManager* InInventoryUIManager, const FGameplayTag& InContainerId, const int32 InMaxSlots,
	int32 InColumns)
{
	InventoryUIManager = InInventoryUIManager;
	ContainerId = InContainerId;
	MaxSlots = InMaxSlots;
	Columns = InColumns;
}

void UIT_WidgetBase::RefreshSlots(const TArray<int32>& SlotIndices)
{
}
