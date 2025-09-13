// Copyright PixelWarriors Inc.
#include "LabyrinthosMazeGenerator.h"
#include "LabyrinthosMazeData.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h" // Required for the new Root Component

// Sets default values
ALabyrinthosMazeGenerator::ALabyrinthosMazeGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// A simple USceneComponent will act as a clean root for our actor.
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	// Create the component responsible for rendering all of our wall instances.
	WallMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallMeshComponent"));
	WallMeshComponent->SetupAttachment(Root);

	// Create the component responsible for rendering all of our floor instances.
	FloorMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorMeshComponent"));
	FloorMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALabyrinthosMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

	// We no longer call GenerateMaze from here, as the Blueprint will now do it.
}

void ALabyrinthosMazeGenerator::GenerateMaze()
{
	// --- Pre-Flight Safety Checks ---
	// It's critical to ensure all required data and meshes have been assigned in the editor.
	// If any of these are missing, we log an error and abort to prevent a crash.
	if (!MazeData)
	{
		UE_LOG(LogTemp, Error, TEXT("FATAL: MazeData is not assigned in the BP_MazeGenerator instance! Aborting maze generation."));
		return;
	}
	if (!WallMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("FATAL: WallMesh is not assigned in the BP_MazeGenerator instance! Aborting maze generation."));
		return;
	}
	if (!FloorMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("FATAL: FloorMesh is not assigned in the BP_MazeGenerator instance! Aborting maze generation."));
		return;
	}

	// --- Component Setup ---
	// Assign the chosen static meshes to their respective Instanced Static Mesh Components.
	WallMeshComponent->SetStaticMesh(WallMesh);
	FloorMeshComponent->SetStaticMesh(FloorMesh);

	// Before generating a new maze, clear any instances from a previous generation.
	WallMeshComponent->ClearInstances();
	FloorMeshComponent->ClearInstances();

	// Define the size of our grid cells. This assumes our meshes (like SM_Cube) are 100x100 units.
	const float CellSize = 100.0f;

	// --- Generation Loop ---
	// Iterate over each FString (row) in our Data Asset's MazeRows array.
	for (int32 RowIndex = 0; RowIndex < MazeData->MazeRows.Num(); ++RowIndex)
	{
		const FString& RowString = MazeData->MazeRows[RowIndex];

		// Then, iterate over each character (column) in the current FString.
		for (int32 ColIndex = 0; ColIndex < RowString.Len(); ++ColIndex)
		{
			// Calculate the world-space position for this grid cell.
			const float XPos = RowIndex * CellSize;
			const float YPos = ColIndex * CellSize;
			const FVector InstanceLocation(XPos, YPos, 0.0f);
			const FTransform InstanceTransform(InstanceLocation);

			// Check the character at the current row and column.
			if (RowString[ColIndex] == 'W')
			{
				// If it's a 'W', it's a wall. Add an instance to the Wall component.
				WallMeshComponent->AddInstance(InstanceTransform);
			}
			else
			{
				// If it's any other character, we treat it as a path. Add an instance to the Floor component.
				FloorMeshComponent->AddInstance(InstanceTransform);
			}
		}
	}

	// Log a success message to the Output Log with the final counts.
	UE_LOG(LogTemp, Warning, TEXT("Maze generation complete. Spawned %d Walls and %d Floors."), WallMeshComponent->GetInstanceCount(), FloorMeshComponent->GetInstanceCount());
}