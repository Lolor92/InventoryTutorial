#include "Inventory/Mutator/IT_InventoryMutator.h"

FAddItemResponse FIT_InventoryMutator::AddItem(FInventoryEntryArray& Inventory, const FAddItemRequest& Request)
{
	FAddItemResponse Response;
	Response.Result = EAddItemResult::Failed;
	Response.RequestedQuantity = Request.Quantity;
	Response.AddedQuantity = 0;
	Response.RemainingQuantity = Request.Quantity;
	
	if (!Request.ContainerId.IsValid()) return Response;
	if (!Request.ItemTag.IsValid()) return Response;
	if (Request.Quantity <= 0) return Response;
	
	int32 Remaining = Response.RemainingQuantity;
	
	// First pass: Fill existing stack of the same item
	for (FInventoryEntry& Entry : Inventory.Entries)
	{
		if (Remaining <= 0) break;
		
		if (Entry.ContainerId != Request.ContainerId) continue;
		if (Entry.ItemTag != Request.ItemTag) continue;
		
		const int32 AddedToStack = Remaining;
		Entry.Quantity += AddedToStack;
		Remaining = 0;
		Response.AddedQuantity = AddedToStack;
		
		UE_LOG(LogTemp, Warning, TEXT("Mutator AddItem: Stacking into \nSlot=%d \nCurrentQuantity=%d"),
			Entry.SlotIndex,
			Entry.Quantity);
		
		// Make it explicit that this specific new entry changed.
		Inventory.MarkItemDirty(Entry);
	}
	
	// Second pass: Create new stack in free slot
	while (Remaining > 0)
	{
		// Find the first free slot
		const int32 FreeSlotIndex = 0;
		
		FInventoryEntry NewEntry;
		NewEntry.ContainerId = Request.ContainerId;
		NewEntry.ItemTag = Request.ItemTag;
		NewEntry.Quantity = Request.Quantity;
		NewEntry.SlotIndex = FreeSlotIndex;
		
		Remaining -= NewEntry.Quantity;
		Response.AddedQuantity += NewEntry.Quantity;
		
		UE_LOG(LogTemp, Warning, TEXT("Mutator AddItem: Creating new entry in \nSlot=%d \nQuantity=%d"),
			NewEntry.SlotIndex,
			NewEntry.Quantity);
		
		// We want a reference to the actual stored entry so we can mark it dirty for replication.
		FInventoryEntry& AddedRef = Inventory.Entries.Add_GetRef(NewEntry);
		
		// Make it explicit that this specific new entry changed.
		Inventory.MarkItemDirty(AddedRef);
		
		// Adding or removing entries is a structural change to the FastArray, so MarkArrayDirty() is required.
		Inventory.MarkArrayDirty();
	}
	
	Response.RemainingQuantity = Remaining;
	
	if (Response.AddedQuantity == 0)
	{
		Response.Result = EAddItemResult::Failed;
	}
	else if (Response.RemainingQuantity > 0)
	{
		Response.Result = EAddItemResult::PartialSuccess;
	}
	else
	{
		Response.Result = EAddItemResult::FullSuccess;
	}
	
	return Response;
}
