#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameCore.h"
#include "PopcornGameMode.generated.h"

class ABallActor;
class APlatformActor;
class ABrickActor;

UCLASS()
class APopcornGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APopcornGameMode();

	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Popcorn")
	TSubclassOf<APlatformActor> PlatformClass;

	UPROPERTY(EditAnywhere, Category = "Popcorn")
	TSubclassOf<ABallActor> BallClass;

	UPROPERTY(EditAnywhere, Category = "Popcorn")
	TSubclassOf<ABrickActor> BrickClass;

	UFUNCTION(BlueprintCallable, Category = "Popcorn")
	void LaunchBall(FVector2D Direction, float Speed);

	UFUNCTION(BlueprintCallable, Category = "Popcorn")
	void SpawnBricks(int Rows, int Cols, FVector2D Start, FVector2D Delta);

protected:
	GameCore Core;

	// Spawned actor instances
	UPROPERTY()
	TArray<ABallActor*> SpawnedBallActors;

	UPROPERTY()
	TArray<ABrickActor*> SpawnedBrickActors;

	UPROPERTY()
	APlatformActor* PlatformActorInstance = nullptr;

	// Scale factor mapping core coordinates to UE units
	UPROPERTY(EditAnywhere, Category = "Popcorn")
	float WorldScale = 1.0f;
};
