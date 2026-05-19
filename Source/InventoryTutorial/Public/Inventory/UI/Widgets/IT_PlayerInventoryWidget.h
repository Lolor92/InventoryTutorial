#pragma once

#include "CoreMinimal.h"
#include "IT_WidgetBase.h"
#include "IT_PlayerInventoryWidget.generated.h"


class UIT_InventoryGridWidget;
class UIT_InventoryUIManager;

UCLASS()
class INVENTORYTUTORIAL_API UIT_PlayerInventoryWidget : public UIT_WidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(UIT_InventoryUIManager* InInventoryUIManager, const FGameplayTag& InContainerId,
		const int32 InMaxSlots, int32 InColumns) override;
	
	virtual void RefreshSlots(const TArray<int32>& SlotIndices) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Inventory|UI")
	TObjectPtr<UIT_InventoryGridWidget> GridWidget = nullptr;
};
