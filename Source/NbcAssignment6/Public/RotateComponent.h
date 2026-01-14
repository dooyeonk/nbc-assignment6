#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NBCASSIGNMENT6_API URotateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URotateComponent();
	
	void SetRotationActive(bool bActive) const;

	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	FRotator RotationSpeed = FRotator(0.0f, 100.0f, 0.0f);
	
	UPROPERTY(EditAnywhere, Category = "Rotation Settings", meta = (ClampMin = "1.0"))
	float UpdatesPerSecond = 60.0f;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	float ReverseEventFrequency = 5.0f;
	
	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	bool bReverseEventOn = true;
	
private:
	void UpdateRotation() const;
	void ReverseRotation();
	
	FTimerHandle RotateTimerHandle;
	float ActualInterval;
	
	FTimerHandle ReverseEventTimerHandle;
};
