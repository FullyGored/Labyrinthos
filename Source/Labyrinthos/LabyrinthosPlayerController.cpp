// Copyright PixelWarriors Inc.

#include "LabyrinthosPlayerController.h"
#include "Blueprint/UserWidget.h" // We need this include for the CreateWidget function to work.

// Define our custom log category that we declared in the .h file
DEFINE_LOG_CATEGORY(LogLabyrinthosPlayerController);


// --- CONSTRUCTOR & INITIALIZATION ---------------------------------------------

ALabyrinthosPlayerController::ALabyrinthosPlayerController()
{
	// Constructor remains clean.
}


// --- LIFECYCLE OVERRIDES ------------------------------------------------------

void ALabyrinthosPlayerController::BeginPlay()
{
	// Always call the parent class's implementation first
	Super::BeginPlay();

	UE_LOG(LogLabyrinthosPlayerController, Log, TEXT("ALabyrinthosPlayerController has begun play!"));

	// --- UI CREATION ---
	// Check if the designer has assigned a Blueprint class to our CommonRootWidgetClass property.
	if (CommonRootWidgetClass)
	{
		// Create the widget instance. 'this' specifies that this PlayerController is the "owner" of the widget.
		CommonRootWidget = CreateWidget<UUserWidget>(this, CommonRootWidgetClass);

		// Check if the widget was created successfully before trying to use it.
		if (CommonRootWidget)
		{
			// Add the widget to the player's screen.
			CommonRootWidget->AddToViewport();
			UE_LOG(LogLabyrinthosPlayerController, Log, TEXT("Common Root Widget created and added to viewport successfully."));
		}
		else
		{
			UE_LOG(LogLabyrinthosPlayerController, Error, TEXT("Failed to create Common Root Widget!"));
		}
	}
	else
	{
		UE_LOG(LogLabyrinthosPlayerController, Warning, TEXT("CommonRootWidgetClass is not set in BP_LabyrinthosPlayerController! No root UI will be created."));
	}
}