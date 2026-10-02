#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

UCLASS()
class APlatformActor : public AActor
{
	GENERATED_BODY()

public:
	APlatformActor();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	// Movement
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void MoveLeft(float Value);

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void SetPlatformX(float X);

	UFUNCTION(BlueprintCallable, Category = "Platform")
	float GetPlatformX() const;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
