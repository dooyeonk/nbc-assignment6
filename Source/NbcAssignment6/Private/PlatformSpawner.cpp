#include "PlatformSpawner.h"
#include "BasePlatform.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnInterval > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&APlatformSpawner::Spawn,
			SpawnInterval,
			true
		);
	}
	else
	{
		for (int i = 0; i < SpawnCount; ++i)
		{
			Spawn();
		}
	}
}

void APlatformSpawner::Spawn()
{
	if (!PlatformClass || !GetWorld()) { return; }

	if (SpawnedCount >= SpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(
		SpawnArea->GetComponentLocation(),
		SpawnArea->GetScaledBoxExtent()
	);
	ABasePlatform* NewPlatform = GetWorld()->SpawnActor<ABasePlatform>(
		PlatformClass,
		Location,
		FRotator::ZeroRotator
	);

	if (!NewPlatform) { return; }
	NewPlatform->InitRandom();
	SpawnedCount++;
}
