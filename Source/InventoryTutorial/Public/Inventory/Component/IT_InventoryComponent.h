#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/Mutator/IT_InventoryMutator.h"
#include "Inventory/Types/Requests/IT_RequestTypes.h"
#include "Inventory/Replication/IT_InventoryFastArray.h"
#include "Inventory/Types/Config/IT_ContainerConfig.h"
#include "IT_InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYTUTORIAL_API UIT_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UIT_InventoryComponent();
	
	int32 GetContainerMaxSlots(const FGameplayTag& ContainerId) const;
	
	// Add Item
	UFUNCTION(BlueprintCallable, Category = "Inventory|Request")
	void RequestAddItem(const FAddItemRequest& Request);
	UFUNCTION(Server, Reliable)
	void ServerRequestAddItem(const FAddItemRequest& Request);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Authority")
	bool TryAddItemAuthority(const FAddItemRequest& Request, FAddItemResponse& OutResponse);
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TArray<FContainerConfig> ContainerConfigs;
	
	UPROPERTY(Replicated)
	FInventoryEntryArray Inventory;
	
private:
	FIT_InventoryMutator InventoryMutator;
};
