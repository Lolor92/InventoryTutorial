#pragma once

#include "CoreMinimal.h"
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
	void ToggleInventoryWidget();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
	void OpenInventoryWidget();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
	void CloseInventoryWidget();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void InitializeUIManager();

private:
	void UpdateInputMode(bool bInventoryOpen);
	
	UPROPERTY(Transient)
	TObjectPtr<UIT_InventoryComponent> InventoryComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory|UI")
	TSubclassOf<UIT_PlayerInventoryWidget> InventoryWidgetClass;
	
	UPROPERTY(Transient)
	TObjectPtr<UIT_PlayerInventoryWidget> ActiveInventoryWidget = nullptr;
};
