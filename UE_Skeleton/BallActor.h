#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class ABallActor : public AActor
{
	GENERATED_BODY()

public:
	ABallActor();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Ball")
	void Launch(FVector2D Direction, float Speed);

	UFUNCTION(BlueprintCallable, Category = "Ball")
	void SetBallPosition(FVector2D Pos);

	UFUNCTION(BlueprintCallable, Category = "Ball")
	FVector2D GetBallPosition() const;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	FVector2D Velocity;
};
