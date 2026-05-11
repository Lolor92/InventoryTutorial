#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "IT_ContainerConfig.generated.h"

class UIT_WidgetBase;

USTRUCT(BlueprintType)
struct FContainerConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FGameplayTag ContainerId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 MaxSlots = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 Columns = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TSubclassOf<UIT_WidgetBase> WidgetClass;
};
