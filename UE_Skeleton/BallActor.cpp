#include "BallActor.h"
#include "Components/StaticMeshComponent.h"

ABallActor::ABallActor()
{
    PrimaryActorTick.bCanEverTick = true;
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = MeshComponent;
}

void ABallActor::BeginPlay()
{
    Super::BeginPlay();
}

void ABallActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // crude physics: translate by velocity
    FVector NewLocation = GetActorLocation();
    NewLocation.X += Velocity.x * DeltaSeconds;
    NewLocation.Z += Velocity.y * DeltaSeconds; // using Z for vertical
    SetActorLocation(NewLocation);
}

void ABallActor::Launch(FVector2D Direction, float Speed)
{
    Velocity = Direction * Speed;
}

void ABallActor::SetBallPosition(FVector2D Pos)
{
    SetActorLocation(FVector(Pos.X, 0.0f, Pos.Y));
}

FVector2D ABallActor::GetBallPosition() const
{
    FVector loc = GetActorLocation();
    return FVector2D(loc.X, loc.Z);
}
