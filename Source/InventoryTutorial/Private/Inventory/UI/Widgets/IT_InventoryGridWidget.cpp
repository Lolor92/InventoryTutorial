#include "Inventory/UI/Widgets/IT_InventoryGridWidget.h"
#include "Components/UniformGridPanel.h"
#include "Inventory/UI/Widgets/IT_InventorySlotWidget.h"

void UIT_InventoryGridWidget::InitGridWidget(UIT_InventoryUIManager* InInventoryUIManager, const FGameplayTag& InContainerId,
		const int32 InMaxSlots, int32 InColumns)
{
	InventoryUIManager = InInventoryUIManager;
	ContainerId = InContainerId;
	MaxSlots = InMaxSlots;
	Columns = InColumns;
	
	BuildGrid();
}

void UIT_InventoryGridWidget::BuildGrid()
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
	
	SlotGridPanel->ClearChildren();
	
	for (int32 SlotIndex = 0; SlotIndex < MaxSlots; SlotIndex++)
	{
		const int32 Row = SlotIndex / Columns;
		const int32 Column = SlotIndex % Columns;
		
		UIT_InventorySlotWidget* SlotWidget = CreateWidget<UIT_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		if (!SlotWidget) continue;
		
		SlotWidget->InitSlotWidget(InventoryUIManager, ContainerId, SlotIndex);
		SlotGridPanel->AddChildToUniformGrid(SlotWidget, Row, Column);
	}
}
