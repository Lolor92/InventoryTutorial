#include "Inventory/UI/Widgets/IT_PlayerInventoryWidget.h"
#include "Inventory/UI/Widgets/IT_InventoryGridWidget.h"

void UIT_PlayerInventoryWidget::InitWidget(UIT_InventoryUIManager* InInventoryUIManager,
	const FGameplayTag& InContainerId, const int32 InMaxSlots, int32 InColumns)
{
	Super::InitWidget(InInventoryUIManager, InContainerId, InMaxSlots, InColumns);
	
	if (GridWidget)
	{
		GridWidget->InitGridWidget(InInventoryUIManager, InContainerId, InMaxSlots, InColumns);
	}
}

void UIT_PlayerInventoryWidget::RefreshSlots(const TArray<int32>& SlotIndices)
{
	if (GridWidget)
	{
		GridWidget->RefreshSlots(SlotIndices);
	}
}
