#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrickActor.generated.h"

UENUM()
enum class EBrickType : uint8
{
	Normal,
	Unbreakable,
	MultiHit,
	Teleport
};

UCLASS()
class ABrickActor : public AActor
{
	GENERATED_BODY()

public:
	ABrickActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	EBrickType BrickType;
	int HitPoints;

	void OnHit();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
