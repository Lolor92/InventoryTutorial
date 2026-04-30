#include "Inventory/UI/Widgets/IT_InventoryGridWidget.h"

#include "Components/UniformGridPanel.h"
#include "Inventory/UI/Widgets/IT_InventorySlotWidget.h"

void UIT_InventoryGridWidget::InitGridWidget(UIT_InventoryUIManager* InInventoryUIManager)
{
	InventoryUIManager = InInventoryUIManager;
	BuildTestSlot();
}

void UIT_InventoryGridWidget::BuildTestSlot()
{
	if (!SlotGridPanel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Grid Widget could not find SlotGrid"));
		return;
	}
	
	if (!SlotWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Grid Widget has no SlotWidgetClass set"));
		return;
	}
	
	int32 TestSlotCount = 100;
	int32 TestColumnCount = 10;
	
	SlotGridPanel->ClearChildren();
	
	for (int32 SlotIndex = 0; SlotIndex < TestSlotCount; SlotIndex++)
	{
		const int32 Row = SlotIndex / TestColumnCount;
		const int32 Column = SlotIndex % TestColumnCount;
		
		UIT_InventorySlotWidget* SlotWidget = CreateWidget<UIT_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		if (!SlotWidget) continue;
		
		SlotWidget->InitSlotWidget(InventoryUIManager, SlotIndex);
		SlotGridPanel->AddChildToUniformGrid(SlotWidget, Row, Column);
	}
}
