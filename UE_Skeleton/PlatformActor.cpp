#include "PlatformActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameCore.h"

APlatformActor::APlatformActor()
{
    PrimaryActorTick.bCanEverTick = true;
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = MeshComponent;
}

void APlatformActor::BeginPlay()
{
    Super::BeginPlay();
}

void APlatformActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Example: apply input-based movement; actual integration with GameCore occurs in GameMode or separate component
}

void APlatformActor::MoveLeft(float Value)
{
    AddActorLocalOffset(FVector(-Value, 0.0f, 0.0f));
}

void APlatformActor::MoveRight(float Value)
{
    AddActorLocalOffset(FVector(Value, 0.0f, 0.0f));
}

void APlatformActor::SetPlatformX(float X)
{
    FVector loc = GetActorLocation();
    loc.X = X;
    SetActorLocation(loc);
}

float APlatformActor::GetPlatformX() const
{
    return GetActorLocation().X;
}
