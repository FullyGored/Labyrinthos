// Copyright PixelWarriors Inc.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabyrinthosMazeGenerator.generated.h"

// Forward-declare the classes we'll be using in the header.
// This is more efficient than including the full header file here.
class ULabyrinthosMazeData;
class UInstancedStaticMeshComponent;

UCLASS()
class LABYRINTHOS_API ALabyrinthosMazeGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALabyrinthosMazeGenerator();

	// The Data Asset that defines the maze layout. Assign this in the Unreal Editor.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Generation")
	TObjectPtr<ULabyrinthosMazeData> MazeData;

	// The Static Mesh to use for the maze walls. Assign this in the Unreal Editor.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Generation")
	TObjectPtr<UStaticMesh> WallMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// A helper function to keep our BeginPlay clean. This is where the core logic lives.
	void GenerateMaze();

	// The component that will hold all our wall instances for high performance.
	UPROPERTY(VisibleAnywhere, Category = "Maze Components")
	TObjectPtr<UInstancedStaticMeshComponent> InstancedStaticMeshComponent;
};