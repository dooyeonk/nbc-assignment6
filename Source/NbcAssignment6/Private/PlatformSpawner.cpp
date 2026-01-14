#include "PlatformSpawner.h"
#include "BasePlatform.h"
#include "ShuttleMoveComponent.h"
#include "RotateComponent.h"
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

	int32 RandomAction = FMath::RandRange(0, 2);
	const bool bWillMove = (RandomAction == 0 || RandomAction == 2);
	const bool bWillRotate = (RandomAction == 1 || RandomAction == 2);

	if (auto* MoveComp = NewPlatform->ShuttleMoveComponent)
	{
		MoveComp->SetMovementActive(bWillMove);
		if (bWillMove)
		{
			MoveComp->Velocity = FMath::RandRange(300.f, 1000.f);
			MoveComp->MaxRange = FVector(FMath::RandRange(700.f, 1500.f), 0, 0);
		}
	}

	if (auto* RotateComp = NewPlatform->RotateComponent)
	{
		RotateComp->SetRotationActive(bWillRotate);
		if (bWillRotate)
		{
			RotateComp->RotationSpeed = FRotator(0, FMath::RandRange(-150.f, 150.f), 0);
		}
	}
}
