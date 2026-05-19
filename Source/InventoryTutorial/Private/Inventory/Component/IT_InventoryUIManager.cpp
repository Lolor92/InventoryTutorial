#include "Inventory/Component/IT_InventoryUIManager.h"
#include "Inventory/Component/IT_InventoryComponent.h"
#include "Inventory/UI/Widgets/IT_PlayerInventoryWidget.h"


UIT_InventoryUIManager::UIT_InventoryUIManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UIT_InventoryUIManager::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeUIManager();
}

void UIT_InventoryUIManager::InitializeUIManager()
{
	InventoryComponent = GetOwner() ? GetOwner()->FindComponentByClass<UIT_InventoryComponent>() : nullptr;
	if (!InventoryComponent) return;
	
	InventoryComponent->OnSlotChanged.AddUObject(this, &UIT_InventoryUIManager::HandleSlotsChanged);
}

void UIT_InventoryUIManager::HandleSlotsChanged(const FGameplayTag ContainerTag, const TArray<int32>& SlotIndices)
{
	if (!ContainerTag.IsValid() || SlotIndices.Num() == 0) return;
	
	TObjectPtr<UIT_WidgetBase>* FoundWindow = ActiveWidget.Find(ContainerTag);
	if (!FoundWindow) return;
	
	(*FoundWindow)->RefreshSlots(SlotIndices);
}

void UIT_InventoryUIManager::ToggleWidget(const FGameplayTag& ContainerId)
{
	if (ActiveWidget.Find(ContainerId))
	{
		CloseWidget(ContainerId);
		return;
	}
	
	OpenWidget(ContainerId);
}

void UIT_InventoryUIManager::OpenWidget(const FGameplayTag& ContainerId)
{
	if (ActiveWidget.Contains(ContainerId)) return;
	
	if (!InventoryComponent) return;
	
	const FContainerConfig* Config = InventoryComponent->GetContainerConfig(ContainerId);
	if (!Config || !Config->WidgetClass) return;
	
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController) return;
	
	UIT_WidgetBase* NewWidget = CreateWidget<UIT_WidgetBase>(PlayerController, Config->WidgetClass);
	if (!NewWidget) return;
	
	NewWidget->InitWidget(this, ContainerId, Config->MaxSlots, Config->Columns);
	NewWidget->AddToViewport();
	
	ActiveWidget.Add(ContainerId, NewWidget);
	
	UpdateInputMode(true);
}

void UIT_InventoryUIManager::CloseWidget(const FGameplayTag& ContainerId)
{
	if (auto FoundWidget = ActiveWidget.Find(ContainerId))
	{
		if (*FoundWidget)
		{
			(*FoundWidget)->RemoveFromParent();
		}
		
		ActiveWidget.Remove(ContainerId);
		UpdateInputMode(false);
	}
}

void UIT_InventoryUIManager::UpdateInputMode(bool bInventoryOpen)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController) return;
	
	if (bInventoryOpen)
	{
		PlayerController->bShowMouseCursor = true;
		
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		
		PlayerController->SetInputMode(InputMode);
		return;
	}
	
	PlayerController->bShowMouseCursor = false;
	
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
}
