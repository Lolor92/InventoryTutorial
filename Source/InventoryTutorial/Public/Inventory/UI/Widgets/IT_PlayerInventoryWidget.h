#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IT_PlayerInventoryWidget.generated.h"


class UIT_InventoryGridWidget;
class UIT_InventoryUIManager;

UCLASS()
class INVENTORYTUTORIAL_API UIT_PlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitInventoryWidget(UIT_InventoryUIManager* InInventoryUIManager);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory|UI")
	TObjectPtr<UIT_InventoryUIManager> InventoryUIManager = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Inventory|UI")
	TObjectPtr<UIT_InventoryGridWidget> GridWidget = nullptr;
};
