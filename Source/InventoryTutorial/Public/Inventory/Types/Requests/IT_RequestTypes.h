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

USTRUCT(BlueprintType)
struct FRemoveItemRequest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FGameplayTag ContainerId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 SlotIndex = INDEX_NONE;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 Quantity = 1;
};

UENUM(BlueprintType)
enum class ERemoveItemResult : uint8
{
	FullSuccess,
	PartialSuccess,
	Failed
};

USTRUCT(BlueprintType)
struct FRemoveItemResponse
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	ERemoveItemResult Result = ERemoveItemResult::Failed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 RequestedQuantity = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 RemovedQuantity = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 RemainingQuantity = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 RemainingInSlot = 0;
};
