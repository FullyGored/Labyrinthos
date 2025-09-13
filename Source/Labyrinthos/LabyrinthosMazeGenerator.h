// Copyright PixelWarriors Inc.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabyrinthosMazeGenerator.generated.h"

class ULabyrinthosMazeData;
class UInstancedStaticMeshComponent;

UCLASS()
class LABYRINTHOS_API ALabyrinthosMazeGenerator : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ALabyrinthosMazeGenerator();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Generation")
    TObjectPtr<ULabyrinthosMazeData> MazeData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Generation")
    TObjectPtr<UStaticMesh> WallMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Generation")
    TObjectPtr<UStaticMesh> FloorMesh;

    UFUNCTION(BlueprintCallable, Category = "Maze Generation")
    void GenerateMaze();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Maze Components")
    TObjectPtr<UInstancedStaticMeshComponent> WallMeshComponent;

    UPROPERTY(VisibleAnywhere, Category = "Maze Components")
    TObjectPtr<UInstancedStaticMeshComponent> FloorMeshComponent;
};