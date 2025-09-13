// Copyright PixelWarriors Inc.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LabyrinthosMazeData.generated.h"

/**
 * A simple struct to hold one row of our maze layout.
 * UPROPERTYs do not support nested TArrays, so this is the standard pattern.
 */
USTRUCT(BlueprintType)
struct FMazeRow
{
	GENERATED_BODY()

	// An array of booleans representing the columns in this row. True = Wall, False = Path.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Layout")
	TArray<bool> Columns;
};

/**
 * UPrimaryDataAsset that holds the layout for a single maze.
 * Create a new Blueprint based on this class to define a new maze level.
 */
UCLASS(BlueprintType)
class LABYRINTHOS_API ULabyrinthosMazeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// The 2D layout of the maze. Each element in the array is a row.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Layout")
	TArray<FMazeRow> MazeLayout;
};