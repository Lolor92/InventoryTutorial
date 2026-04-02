#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "IT_ContainerConfig.generated.h"

USTRUCT(BlueprintType)
struct FContainerConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FGameplayTag ContainerId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 MaxSlots = 100;
};
