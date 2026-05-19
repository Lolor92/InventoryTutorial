#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "IT_InventoryUIManager.generated.h"


class UIT_WidgetBase;
class UIT_PlayerInventoryWidget;
class UIT_InventoryComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYTUTORIAL_API UIT_InventoryUIManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UIT_InventoryUIManager();

	UFUNCTION(BlueprintPure, Category = "Inventory|UI")
	UIT_InventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
	void ToggleWidget(const FGameplayTag& ContainerId);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
	void OpenWidget(const FGameplayTag& ContainerId);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
	void CloseWidget(const FGameplayTag& ContainerId);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void InitializeUIManager();
	
	UFUNCTION()
	void HandleSlotsChanged(const FGameplayTag ContainerTag, const TArray<int32>& SlotIndices);

private:
	void UpdateInputMode(bool bInventoryOpen);
	
	UPROPERTY(Transient)
	TObjectPtr<UIT_InventoryComponent> InventoryComponent = nullptr;
	
	UPROPERTY(Transient)
	TMap <FGameplayTag, TObjectPtr<UIT_WidgetBase>> ActiveWidget;
};
