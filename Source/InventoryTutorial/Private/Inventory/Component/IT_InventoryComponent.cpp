#include "Inventory/Component/IT_InventoryComponent.h"
#include "Net/UnrealNetwork.h"


UIT_InventoryComponent::UIT_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UIT_InventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, Inventory);
}

void UIT_InventoryComponent::RequestAddItem(const FAddItemRequest& Request)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FAddItemResponse Response;
		TryAddItemAuthority(Request, Response);
		return;
	}
	ServerRequestAddItem(Request);
}

void UIT_InventoryComponent::ServerRequestAddItem_Implementation(const FAddItemRequest& Request)
{
	FAddItemResponse Response;
	TryAddItemAuthority(Request, Response);
}

bool UIT_InventoryComponent::TryAddItemAuthority(const FAddItemRequest& Request, FAddItemResponse& OutResponse)
{
	OutResponse.Result = EAddItemResult::Failed;
	OutResponse.RequestedQuantity = Request.Quantity;
	OutResponse.AddedQuantity = 0;
	OutResponse.RemainingQuantity = Request.Quantity;
	
	if (GetOwner() && !GetOwner()->HasAuthority()) return false;
	
	if (!Request.ContainerId.IsValid()) return false;
	if (!Request.ItemTag.IsValid()) return false;
	if (Request.Quantity <= 0) return false;
	
	const int32 ContainerMaxSlots = GetContainerMaxSlots(Request.ContainerId);
	const int32 ItemMaxStackSize = GetItemMaxStackSize(Request.ItemTag);
	
	const FAddItemResponse Response = InventoryMutator.AddItem(Inventory, Request, ContainerMaxSlots, ItemMaxStackSize);
	
	OutResponse = Response;
	
	UE_LOG(LogTemp, Warning, TEXT("TryAddItemAuthority Result: \nAdded=%d \nRemaining=%d \nResult=%s"),
		OutResponse.AddedQuantity,
		OutResponse.RemainingQuantity,
		*StaticEnum<EAddItemResult>()->GetNameStringByValue(static_cast<int>(OutResponse.Result)));
	
	return OutResponse.AddedQuantity > 0;
}

void UIT_InventoryComponent::RequestRemoveItem(const FRemoveItemRequest& Request)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FRemoveItemResponse Response;
		TryRemoveItemAuthority(Request, Response);
		return;
	}
	
	ServerRequestRemoveItem(Request);
}

void UIT_InventoryComponent::ServerRequestRemoveItem_Implementation(const FRemoveItemRequest& Request)
{
	FRemoveItemResponse Response;
	TryRemoveItemAuthority(Request, Response);
}

bool UIT_InventoryComponent::TryRemoveItemAuthority(const FRemoveItemRequest& Request, FRemoveItemResponse& OutResponse)
{
	OutResponse.Result = ERemoveItemResult::Failed;
	OutResponse.RequestedQuantity = Request.Quantity;
	OutResponse.RemovedQuantity = 0;
	OutResponse.RemainingQuantity = Request.Quantity;
	OutResponse.RemainingInSlot = 0;
	
	if (GetOwner() && !GetOwner()->HasAuthority()) return false;
	if (!Request.ContainerId.IsValid()) return false;
	if (Request.SlotIndex < 0) return false;
	if (Request.Quantity <= 0) return false;
	
	const FRemoveItemResponse Response = InventoryMutator.RemoveItem(Inventory, Request);
	
	OutResponse = Response;
	
	UE_LOG(LogTemp, Warning, TEXT("TryRemoveItemAuthority Result: \nRemoved=%d \nRemaining=%d \nRemainingInSlot=%d \nResult=%s"),
		OutResponse.RemovedQuantity,
		OutResponse.RemainingQuantity,
		OutResponse.RemainingInSlot,
		*StaticEnum<ERemoveItemResult>()->GetNameStringByValue(static_cast<int>(OutResponse.Result)));
	
	return OutResponse.RemainingQuantity > 0;
}

int32 UIT_InventoryComponent::GetContainerMaxSlots(const FGameplayTag& ContainerId) const
{
	for (const FContainerConfig Config : ContainerConfigs)
	{
		if (Config.ContainerId == ContainerId)
		{
			return Config.MaxSlots;
		}
	}
	
	return 0;
}

int32 UIT_InventoryComponent::GetItemMaxStackSize(const FGameplayTag& ItemTag) const
{
	if (!ItemDatabase) return 0;
	
	const UIT_ItemDefinition* Def = ItemDatabase->GetItemDefinitionByTag(ItemTag);
	if (!Def) return 0;
	
	return Def->bStackable ? FMath::Max(1, Def->MaxStackSize) : 1;
}
