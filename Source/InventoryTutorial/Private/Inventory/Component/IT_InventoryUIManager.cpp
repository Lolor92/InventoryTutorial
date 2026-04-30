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
}


void UIT_InventoryUIManager::ToggleInventoryWidget()
{
	if (ActiveInventoryWidget)
	{
		CloseInventoryWidget();
		return;
	}
	
	OpenInventoryWidget();
}

void UIT_InventoryUIManager::OpenInventoryWidget()
{
	if (ActiveInventoryWidget) return;
	
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController) return;
	
	ActiveInventoryWidget = CreateWidget<UIT_PlayerInventoryWidget>(PlayerController, InventoryWidgetClass);
	if (!ActiveInventoryWidget) return;
	
	ActiveInventoryWidget->InitInventoryWidget(this);
	
	ActiveInventoryWidget->AddToViewport();
	
	UpdateInputMode(true);
}

void UIT_InventoryUIManager::CloseInventoryWidget()
{
	if (!ActiveInventoryWidget) return;
	
	ActiveInventoryWidget->RemoveFromParent();
	ActiveInventoryWidget = nullptr;
	
	UpdateInputMode(false);
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
