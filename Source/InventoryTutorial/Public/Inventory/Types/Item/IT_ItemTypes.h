#pragma once

#include "CoreMinimal.h"
#include "IT_ItemTypes.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common,
	Rare,
	Epic,
	Legendary
};
