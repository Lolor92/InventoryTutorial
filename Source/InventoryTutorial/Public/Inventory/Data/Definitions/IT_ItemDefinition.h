#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "IT_ItemDefinition.generated.h"


UCLASS(BlueprintType)
class INVENTORYTUTORIAL_API UIT_ItemDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	bool bStackable = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory",
		meta=(ClampMin="1", EditCondition="bStackable", EditConditionHides))
	int32 MaxStackSize = 1;
};
