#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class NBCASSIGNMENT6_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
    
public: 
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	FVector MaxRange;

	FVector StartLocation;

	float Direction = 1.0f;
};
