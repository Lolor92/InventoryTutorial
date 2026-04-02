#include "Inventory/Mutator/IT_InventoryMutator.h"

FAddItemResponse FIT_InventoryMutator::AddItem(FInventoryEntryArray& Inventory, const FAddItemRequest& Request,
	const int32 ContainerMaxSlots, const int32 ItemMaxStackSize)
{
	FAddItemResponse Response;
	Response.Result = EAddItemResult::Failed;
	Response.RequestedQuantity = Request.Quantity;
	Response.AddedQuantity = 0;
	Response.RemainingQuantity = Request.Quantity;
	
	if (!Request.ContainerId.IsValid()) return Response;
	if (!Request.ItemTag.IsValid()) return Response;
	if (Request.Quantity <= 0) return Response;
	if (ContainerMaxSlots <= 0) return Response;
	if (ItemMaxStackSize <= 0) return Response;
	
	int32 Remaining = Response.RemainingQuantity;
	
	// First pass: Fill existing stack of the same item
	for (FInventoryEntry& Entry : Inventory.Entries)
	{
		if (Remaining <= 0) break;
		
		if (Entry.ContainerId != Request.ContainerId) continue;
		if (Entry.ItemTag != Request.ItemTag) continue;
		if (Entry.Quantity >= ItemMaxStackSize) continue;
		
		const int32 SpaceLeft = ItemMaxStackSize - Entry.Quantity;
		const int32 ToAdd = FMath::Min(SpaceLeft, Remaining);
		if (ToAdd <= 0) continue;
		
		// Increase the stack
		Entry.Quantity += ToAdd;
		// Reduce what is still left to place
		Remaining -= ToAdd;
		// Record how much the operation successfully added
		Response.AddedQuantity += ToAdd;
		
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
		const int32 FreeSlotIndex = FindFirstFreeSlot(Inventory, Request.ContainerId, ContainerMaxSlots);
		if (FreeSlotIndex == INDEX_NONE) break;
		
		/* If remaining is smaller than max stack, use all of it
		 * otherwise create a full stack and keep looping for the rest */
		const int32 NewQuantity = FMath::Min(Remaining, ItemMaxStackSize);
		
		FInventoryEntry NewEntry;
		NewEntry.ContainerId = Request.ContainerId;
		NewEntry.ItemTag = Request.ItemTag;
		NewEntry.Quantity = NewQuantity;
		NewEntry.SlotIndex = FreeSlotIndex;
		
		Remaining -= NewQuantity;
		Response.AddedQuantity += NewQuantity;
		
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

int32 FIT_InventoryMutator::FindFirstFreeSlot(const FInventoryEntryArray& Inventory, const FGameplayTag& ContainerId,
	int32 MaxSlots)
{
	if (!ContainerId.IsValid() || MaxSlots <= 0) return INDEX_NONE;
	
	// Create a bit array to tract which slot indices are already used in the container.
	// It starts with all slots set to false, meaning all slots are considered empty at first.
	TBitArray<> UsedSlots(false, MaxSlots);
	
	// Check every inventory entry to see which slots are already used
	for (const FInventoryEntry& Entry : Inventory.Entries)
	{
		// Only mark slots that belong to this container and are in valid range
		if (Entry.ContainerId == ContainerId && Entry.SlotIndex >= 0 && Entry.SlotIndex < MaxSlots)
		{
			UsedSlots[Entry.SlotIndex] = true;
		}
	}
	
	// Scan from the start and return the first slot that is still free
	for (int32 SlotIndex = 0; SlotIndex < MaxSlots; SlotIndex++)
	{
		if (UsedSlots[SlotIndex]) continue;
		
		return SlotIndex;
	}
	
	return INDEX_NONE;
}
