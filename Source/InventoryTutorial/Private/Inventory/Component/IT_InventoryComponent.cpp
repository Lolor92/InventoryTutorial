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
	
	const FAddItemResponse Response = InventoryMutator.AddItem(Inventory, Request, ContainerMaxSlots);
	
	OutResponse = Response;
	
	UE_LOG(LogTemp, Warning, TEXT("TryAddItemAuthority Result: \nAdded=%d \nRemaining=%d \nResult=%s"),
		OutResponse.AddedQuantity,
		OutResponse.RemainingQuantity,
		*StaticEnum<EAddItemResult>()->GetNameStringByValue(static_cast<int>(OutResponse.Result)));
	
	return OutResponse.AddedQuantity > 0;
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
