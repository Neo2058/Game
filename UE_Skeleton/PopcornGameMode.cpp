#include "PopcornGameMode.h"
#include "GameCore.h"
#include "Kismet/GameplayStatics.h"
#include "BallActor.h"
#include "PlatformActor.h"
#include "BrickActor.h"


APopcornGameMode::APopcornGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APopcornGameMode::StartPlay()
{
    Super::StartPlay();
    // Initialize game core
    // Spawn platform actor if class provided
    if (PlatformClass)
    {
        PlatformActorInstance = GetWorld()->SpawnActor<APlatformActor>(PlatformClass, FVector::ZeroVector, FRotator::ZeroRotator);
    }
}

void APopcornGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Update game core
    Core.Update(DeltaSeconds);

    // Sync balls
    for (size_t i = 0; i < Core.balls.size(); ++i)
    {
        if (i < (size_t)SpawnedBallActors.Num())
        {
            ABallActor* actor = SpawnedBallActors[i];
            if (actor && Core.balls[i].active)
            {
                FVector loc(Core.balls[i].pos.x * WorldScale, 0.0f, Core.balls[i].pos.y * WorldScale);
                actor->SetActorLocation(loc);
            }
        }
    }

    // Sync platform
    if (PlatformActorInstance)
    {
        FVector platLoc(Core.platform.x * WorldScale, 0.0f, 180.0f * WorldScale);
        PlatformActorInstance->SetActorLocation(platLoc);
    }
}

void APopcornGameMode::LaunchBall(FVector2D Direction, float Speed)
{
    Core.LaunchBall({Direction.X, Direction.Y}, Speed);

    // spawn actor
    if (BallClass)
    {
        ABallActor* actor = GetWorld()->SpawnActor<ABallActor>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator);
        if (actor)
        {
            actor->Launch(Direction, Speed);
            SpawnedBallActors.Add(actor);
        }
    }
}

void APopcornGameMode::SpawnBricks(int Rows, int Cols, FVector2D Start, FVector2D Delta)
{
    InitializeBricks(Core, Rows, Cols, Start.X, Start.Y, Delta.X, Delta.Y);

    if (!BrickClass) return;

    for (const auto &br : Core.bricks)
    {
        FVector loc(br.x * WorldScale, 0.0f, br.y * WorldScale);
        ABrickActor* actor = GetWorld()->SpawnActor<ABrickActor>(BrickClass, loc, FRotator::ZeroRotator);
        if (actor)
            SpawnedBrickActors.Add(actor);
    }
}
