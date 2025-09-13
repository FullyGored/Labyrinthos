// Copyright PixelWarriors Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Logging/LogMacros.h"
#include "LabyrinthosPlayerController.generated.h"

class UUserWidget; // Forward declaring the base UserWidget class is the most flexible approach.

// Declares a custom log category for our PlayerController for easier debugging.
DECLARE_LOG_CATEGORY_EXTERN(LogLabyrinthosPlayerController, Log, All);

/**
 * ALabyrinthosPlayerController is the central command hub for the human player.
 * It is responsible for managing player-wide systems that are not tied directly
 * to a pawn, such as the User Interface (UI), and handling input routing.
 */
UCLASS()
class LABYRINTHOS_API ALabyrinthosPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	ALabyrinthosPlayerController();

protected:
	//~ Begin APlayerController Interface
	virtual void BeginPlay() override;
	//~ End APlayerController Interface

private:
	// The C++ variable that will hold the actual instance of our root UI widget once it's created.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> CommonRootWidget;

	// The Blueprint class that we want to use for our root widget. This is assigned in the editor.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CommonRootWidgetClass;

	// The specific Blueprint class for our in-game HUD. Assigned in the editor.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LabyrinthosHUDClass;
};