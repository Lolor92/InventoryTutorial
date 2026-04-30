#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IT_InventoryGridWidget.generated.h"


class UUniformGridPanel;
class UIT_InventorySlotWidget;
class UIT_InventoryUIManager;

UCLASS()
class INVENTORYTUTORIAL_API UIT_InventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitGridWidget(UIT_InventoryUIManager* InInventoryUIManager);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
	void BuildTestSlot();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory|UI")
	TObjectPtr<UIT_InventoryUIManager> InventoryUIManager = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory|UI")
	TSubclassOf<UIT_InventorySlotWidget> SlotWidgetClass = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Inventory|UI")
	TObjectPtr<UUniformGridPanel> SlotGridPanel = nullptr;
};
