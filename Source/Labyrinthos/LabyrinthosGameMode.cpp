// Copyright PixelWarriors Inc.

#include "LabyrinthosGameMode.h"
#include "LabyrinthosCharacter.h" 

// Define our custom log category that we declared in the .h file
DEFINE_LOG_CATEGORY(LogLabyrinthosGameMode);

// --- CONSTRUCTOR & INITIALIZATION ---------------------------------------------

ALabyrinthosGameMode::ALabyrinthosGameMode()
{
	// Constructor is clean. We do not set default classes here.
	// That is the responsibility of our Blueprint child class.
}

// --- LIFECYCLE OVERRIDES ------------------------------------------------------

void ALabyrinthosGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the game state. Reset counters.
	CurrentOrbCount = 0;

	// Log the game rules for this level for easy debugging.
	UE_LOG(LogLabyrinthosGameMode, Log, TEXT("Labyrinthos Game Started. Player must collect %d orbs to win."), RequiredOrbCount);
}

// --- PUBLIC INTERFACE ---------------------------------------------------------

void ALabyrinthosGameMode::PlayerCollectedOrb()
{
	CurrentOrbCount++;

	UE_LOG(LogLabyrinthosGameMode, Log, TEXT("Player collected an orb. New count: %d / %d"), CurrentOrbCount, RequiredOrbCount);

	// *** CRITICAL STEP ***
	// Broadcast the delegate to notify any listening systems (like the UI).
	// This fires the event we created in the .h file.
	OnOrbCountChanged.Broadcast(CurrentOrbCount, RequiredOrbCount);

	// After updating the count, we immediately check if the player has won.
	CheckWinCondition();
}

// --- PRIVATE IMPLEMENTATION ---------------------------------------------------

void ALabyrinthosGameMode::CheckWinCondition()
{
	// Using >= is safer than ==
	if (CurrentOrbCount >= RequiredOrbCount)
	{
		// VICTORY!
		UE_LOG(LogLabyrinthosGameMode, Warning, TEXT("WIN CONDITION MET! Player has collected all orbs."));
	}
}