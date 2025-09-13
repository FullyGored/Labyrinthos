// Copyright PixelWarriors Inc.
#include "LabyrinthosMazeGenerator.h"
#include "LabyrinthosMazeData.h"
#include "Components/InstancedStaticMeshComponent.h"

ALabyrinthosMazeGenerator::ALabyrinthosMazeGenerator()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Create the InstancedStaticMeshComponent. This is the key to performance.
    // Instead of thousands of individual actors, we have one component drawing all walls.
    InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
    SetRootComponent(InstancedStaticMeshComponent);
}

void ALabyrinthosMazeGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateMaze();
}

void ALabyrinthosMazeGenerator::GenerateMaze()
{
    // --- Pre-flight Checks ---
    // Ensure we have valid data and meshes assigned in the editor.
    if (!MazeData)
    {
        UE_LOG(LogTemp, Error, TEXT("MazeData is not assigned in %s!"), *GetName());
        return;
    }
    if (!WallMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("WallMesh is not assigned in %s!"), *GetName());
        return;
    }

    // --- Setup ---
    InstancedStaticMeshComponent->SetStaticMesh(WallMesh);

    // Define the size of our maze cells. Assumes a 100x100x100 cube.
    const float CellSize = 100.0f;

    // --- Generation Loop ---
    // We will now read the data and place the instances.
    for (int32 RowIndex = 0; RowIndex < MazeData->MazeRows.Num(); ++RowIndex)
    {
        const FString& RowString = MazeData->MazeRows[RowIndex];
        for (int32 ColIndex = 0; ColIndex < RowString.Len(); ++ColIndex)
        {
            // If the character at this column is 'W' (for Wall)
            if (RowString[ColIndex] == 'W')
            {
                // Calculate the position for this wall instance
                const float XPos = RowIndex * CellSize;
                const float YPos = ColIndex * CellSize;

                FVector InstanceLocation(XPos, YPos, 0.0f);
                FTransform InstanceTransform(InstanceLocation);

                // Add the instance to our component
                InstancedStaticMeshComponent->AddInstance(InstanceTransform);
            }
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Maze generation complete with %d instances."), InstancedStaticMeshComponent->GetInstanceCount());
}