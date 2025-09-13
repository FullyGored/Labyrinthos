// Copyright PixelWarriors Inc.
#pragma once

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
// The generated.h include must always be the last include in the header file.
#include "LabyrinthosOrb.generated.h"

UCLASS()
class LABYRINTHOS_API ALabyrinthosOrb : public AActor
{
    GENERATED_BODY()

public:
    ALabyrinthosOrb();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> OrbMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USphereComponent> CollisionSphere;

    // This is the C++ function that will be called when an overlap occurs.
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    // This is an event that we can implement visually in our Blueprint child class.
    // The C++ will call this, and the Blueprint will decide what VFX/sound to play.
    UFUNCTION(BlueprintImplementableEvent, Category = "Orb Events")
    void OnOrbCollectedFX();

private:
    // Internal function to handle the collection logic
    void HandleOrbCollection(AActor* CollectingActor);
};