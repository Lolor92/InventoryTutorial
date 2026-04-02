#pragma once

#include "CoreMinimal.h"
#include "Inventory/Replication/IT_InventoryFastArray.h"
#include "Inventory/Types/Requests/IT_RequestTypes.h"

class INVENTORYTUTORIAL_API FIT_InventoryMutator
{
public:
	FAddItemResponse AddItem(FInventoryEntryArray& Inventory, const FAddItemRequest& Request, const int32 ContainerMaxSlots);
	
	static int32 FindFirstFreeSlot(const FInventoryEntryArray& Inventory, const FGameplayTag& ContainerId, int32 MaxSlots);
};
