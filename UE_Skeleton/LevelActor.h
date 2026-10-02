#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelActor.generated.h"

UCLASS()
class ALevelActor : public AActor
{
	GENERATED_BODY()

public:
	ALevelActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Level data and management
	TArray<ABrickActor*> Bricks;

	void InitializeLevel(int LevelIndex);
};
