#include "Inventory/Replication/IT_InventoryFastArray.h"
#include "Inventory/Component/IT_InventoryComponent.h"


void FInventoryEntryArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	if (InventoryComponent)
	{
		InventoryComponent->HandleReplicationAdd(AddedIndices);
	}
}

void FInventoryEntryArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	if (InventoryComponent)
	{
		InventoryComponent->HandleReplicationRemove(RemovedIndices);
	}
}

void FInventoryEntryArray::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	if (InventoryComponent)
	{
		InventoryComponent->HandleReplicationChange(ChangedIndices);
	}
}
