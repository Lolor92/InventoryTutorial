#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "IT_InventoryUIManager.generated.h"


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

private:
	void UpdateInputMode(bool bInventoryOpen);
	
	UPROPERTY(Transient)
	TObjectPtr<UIT_InventoryComponent> InventoryComponent = nullptr;
	
	UPROPERTY(Transient)
	TMap <FGameplayTag, TObjectPtr<UUserWidget>> ActiveWidget;
};
