#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShuttleMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NBCASSIGNMENT6_API UShuttleMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShuttleMoveComponent();

	void SetMovementActive(bool bActive) const;
	
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float Velocity = 500.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	FVector MaxRange = FVector(500.0f, 0.0f, 0.0f);
	
	UPROPERTY(EditAnywhere, Category = "Movement Settings", meta = (ClampMin = "1.0"))
	float UpdatesPerSecond = 60.0f;
	
protected:
	virtual void BeginPlay() override;
	
private:	
	void UpdateMovement();
	
	FTimerHandle MoveTimerHandle;
	FVector StartLocation;
	float Direction = 1.0f;
	float ActualInterval;
	
	bool IsMovingReverse() const;
};
