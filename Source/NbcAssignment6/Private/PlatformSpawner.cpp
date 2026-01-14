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
	for (int32 i = 0; i < SpawnCount; i++) { Spawn(); }
}

void APlatformSpawner::Spawn() const
{
	if (!PlatformClass || !GetWorld()) { return; }

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
}
