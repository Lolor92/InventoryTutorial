#include "Inventory/Data/Databases/IT_ItemDatabase.h"

const UIT_ItemDefinition* UIT_ItemDatabase::GetItemDefinitionByTag(const FGameplayTag& ItemTag) const
{
	if (!ItemTag.IsValid()) return nullptr;
	
	for (const UIT_ItemDefinition* ItemDefinition : ItemDefinitions)
	{
		if (IsValid(ItemDefinition) && ItemDefinition->ItemTag == ItemTag)
		{
			return ItemDefinition;
		}
	}
	
	return nullptr;
}
