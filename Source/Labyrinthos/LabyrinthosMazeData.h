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

	/**
	 * This TArray holds the string-based layout for our maze.
	 * Each string in the array is a row. 'W' can represent a wall, and any other character an empty space.
	 * EditAnywhere allows us to edit this directly in the Unreal Editor after creating a Data Asset.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Data")
	TArray<FString> MazeRows;
};