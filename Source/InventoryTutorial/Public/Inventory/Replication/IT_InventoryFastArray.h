#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "IT_InventoryFastArray.generated.h"

/* 
A FastArray in Unreal is a replication pattern for arrays that change often.
Instead of replicating the entire array every time one item changes, Unreal can replicate only the changed entries.
That makes it a good fit for inventories, because items are constantly being added, removed, stacked, or moved.
*/

USTRUCT()
struct FInventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	// ContainerId lets one array hold multiple inventory views.
	// Each entry says which container it belongs to, like Player, Equipment, or SkillBar.
	UPROPERTY()
	FGameplayTag ContainerId;
	
	UPROPERTY()
	FGameplayTag ItemTag;
	
	UPROPERTY()
	int32 SlotIndex = INDEX_NONE;
	
	UPROPERTY()
	int32 Quantity = 0;
	
	bool IsValidEntry() const
	{
		return ItemTag.IsValid() && SlotIndex != INDEX_NONE && Quantity > 0;
	}
};

USTRUCT()
struct FInventoryEntryArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FInventoryEntry> Entries;
	
	// Tells Unreal to replicate Entries using Fast Array delta serialization.
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FInventoryEntry, FInventoryEntryArray>(Entries, DeltaParams, *this);
	}
};

// NetDeltaSerialize(...) defines how to replicate it
// TStructOpsTypeTraits<...> tells Unreal that this struct actually has that custom serializer
template<>
struct TStructOpsTypeTraits<FInventoryEntryArray> : TStructOpsTypeTraitsBase2<FInventoryEntryArray>
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};
