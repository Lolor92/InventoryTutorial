#include "Inventory/UI/Widgets/IT_InventorySlotWidget.h"


void UIT_InventorySlotWidget::InitSlotWidget(UIT_InventoryUIManager* InInventoryUIManager, int32 InSlotIndex)
{
	InventoryUIManager = InInventoryUIManager;
	SlotIndex = InSlotIndex;
}
