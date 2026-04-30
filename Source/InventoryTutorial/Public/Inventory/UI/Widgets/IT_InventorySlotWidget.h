#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IT_InventorySlotWidget.generated.h"


class UIT_InventoryUIManager;

UCLASS()
class INVENTORYTUTORIAL_API UIT_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSlotWidget(UIT_InventoryUIManager* InInventoryUIManager, int32 InSlotIndex);
	
	UFUNCTION(BlueprintPure, Category = "Inventory|UI")
	int32 GetSlotIndex() const { return SlotIndex; }
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory|UI")
	TObjectPtr<UIT_InventoryUIManager> InventoryUIManager = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inventory|UI")
	int32 SlotIndex = INDEX_NONE;
};
