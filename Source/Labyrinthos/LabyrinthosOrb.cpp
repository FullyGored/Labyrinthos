// Copyright PixelWarriors Inc.

#include "LabyrinthosOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "LabyrinthosCharacter.h" // Your player character class
#include "Engine/Engine.h"

ALabyrinthosOrb::ALabyrinthosOrb()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create the collision sphere as root component
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    RootComponent = CollisionSphere;

    // Set up collision sphere
    CollisionSphere->SetSphereRadius(50.0f);
    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionSphere->SetGenerateOverlapEvents(true);

    // Create the mesh component
    OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
    OrbMesh->SetupAttachment(RootComponent);
    OrbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALabyrinthosOrb::BeginPlay()
{
    Super::BeginPlay();

    // Bind the overlap event
    if (CollisionSphere)
    {
        CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ALabyrinthosOrb::OnOverlapBegin);
    }
}

void ALabyrinthosOrb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    // Check if the overlapping actor is the player character
    if (ALabyrinthosCharacter* Player = Cast<ALabyrinthosCharacter>(OtherActor))
    {
        HandleOrbCollection(Player);
    }
}

void ALabyrinthosOrb::HandleOrbCollection(AActor* CollectingActor)
{
    // Call the Blueprint implementable event for VFX/sound
    OnOrbCollectedFX();

    // Add any C++ collection logic here (score, inventory, etc.)
    // Example: Player->AddScore(10);

    // Destroy the orb after a short delay to allow VFX to play
    SetActorEnableCollision(false); // Prevent multiple collections

    // Optional: Add a small delay before destruction
    FTimerHandle DestroyTimer;
    GetWorldTimerManager().SetTimer(DestroyTimer, [this]()
        {
            Destroy();
        }, 0.1f, false); // Destroy after 0.1 seconds
}