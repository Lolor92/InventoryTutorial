#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "IT_WidgetBase.generated.h"


class UIT_InventoryUIManager;

UCLASS()
class INVENTORYTUTORIAL_API UIT_WidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(UIT_InventoryUIManager* InInventoryUIManager, const FGameplayTag& InContainerId, const int32 InMaxSlots, int32 InColumns);
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UIT_InventoryUIManager> InventoryUIManager;
	
	UPROPERTY(Transient)
	FGameplayTag ContainerId;
	
	UPROPERTY(Transient)
	int32 MaxSlots;
	
	UPROPERTY(Transient)
	int32 Columns;
};
