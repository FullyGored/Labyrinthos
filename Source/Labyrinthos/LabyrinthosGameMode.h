// Copyright PixelWarriors Inc.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/LogMacros.h"
#include "LabyrinthosGameMode.generated.h"

// DELEGATE DECLARED IN GLOBAL SCOPE - CORRECT
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrbCountChangedSignature, int32, CurrentOrbCount, int32, RequiredOrbCount);

DECLARE_LOG_CATEGORY_EXTERN(LogLabyrinthosGameMode, Log, All);

UCLASS()
class LABYRINTHOS_API ALabyrinthosGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// The Delegate UPROPERTY MUST BE in the public: section. This is its contract.
	UPROPERTY(BlueprintAssignable, Category = "Labyrinthos|Delegates")
	FOnOrbCountChangedSignature OnOrbCountChanged;

	// The UFUNCTION is a public interface. Correctly placed.
	UFUNCTION(BlueprintCallable, Category = "Labyrinthos|Game Rules")
	void PlayerCollectedOrb();
	void OrbWasCollected();

	// Constructor.
	ALabyrinthosGameMode();

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

private:
	// UPROPERTY marked for editor access but kept private in C++. This is our standard.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Rules", meta = (AllowPrivateAccess = "true"))
	int32 RequiredOrbCount = 5;

	// Pure C++ function. Correctly private.
	void CheckWinCondition();

	// Pure C++ variable. Correctly private.
	int32 CurrentOrbCount = 0;
};