#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "IT_RequestTypes.generated.h"

USTRUCT(BlueprintType)
struct FAddItemRequest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|Request")
	FGameplayTag ContainerId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|Request")
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory|Request")
	int32 Quantity = 1;
};

UENUM(BlueprintType)
enum class EAddItemResult : uint8
{
	FullSuccess,
	PartialSuccess,
	Failed
};

USTRUCT(BlueprintType)
struct FAddItemResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	EAddItemResult Result = EAddItemResult::Failed;
	
	UPROPERTY()
	int32 RequestedQuantity = 0;
	
	UPROPERTY()
	int32 AddedQuantity = 0;
	
	UPROPERTY()
	int32 RemainingQuantity = 0;
};