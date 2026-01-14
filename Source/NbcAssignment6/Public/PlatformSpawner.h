#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class ABasePlatform;
class UBoxComponent;

UCLASS()
class NBCASSIGNMENT6_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformSpawner();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<ABasePlatform> PlatformClass;
	
	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	UBoxComponent* SpawnArea;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 SpawnCount = 30;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnInterval = 0.2f;
private:
	void Spawn();
	
	FTimerHandle SpawnTimerHandle;
	int32 SpawnedCount = 0;
};
