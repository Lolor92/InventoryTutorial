#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Inventory//Data/Definitions/IT_ItemDefinition.h"
#include "IT_ItemDatabase.generated.h"


UCLASS(BlueprintType)
class INVENTORYTUTORIAL_API UIT_ItemDatabase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Database")
	TArray<TObjectPtr<UIT_ItemDefinition>> ItemDefinitions;
	
	UFUNCTION(BlueprintCallable, Category="Database")
	const UIT_ItemDefinition* GetItemDefinitionByTag(const FGameplayTag& ItemTag) const;
};
