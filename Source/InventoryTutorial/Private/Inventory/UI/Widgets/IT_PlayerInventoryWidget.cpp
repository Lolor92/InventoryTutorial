#include "Inventory/UI/Widgets/IT_PlayerInventoryWidget.h"
#include "Inventory/UI/Widgets/IT_InventoryGridWidget.h"

void UIT_PlayerInventoryWidget::InitInventoryWidget(UIT_InventoryUIManager* InInventoryUIManager)
{
	InventoryUIManager = InInventoryUIManager;
	
	if (GridWidget)
	{
		GridWidget->InitGridWidget(InventoryUIManager);
	}
}
