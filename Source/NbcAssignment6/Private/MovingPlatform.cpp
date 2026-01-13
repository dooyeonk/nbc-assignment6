#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRootComponent);

	MoveSpeed = 500.0f;
	MaxRange = FVector(500.0f, 0.0f, 0.0f);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector TargetDestination;

	if (Direction > 0.0f)
	{
		TargetDestination = StartLocation + MaxRange;
	}
	else
	{
		TargetDestination = StartLocation;
	}

	FVector MoveNormal = (TargetDestination - CurrentLocation).GetSafeNormal();
	CurrentLocation += (MoveNormal * MoveSpeed * DeltaTime);
	SetActorLocation(CurrentLocation);

	float DistanceToTarget = FVector::Dist(CurrentLocation, TargetDestination);
	if (DistanceToTarget <= (MoveSpeed * DeltaTime))
	{
		SetActorLocation(TargetDestination);
		Direction *= -1.0f;
	}
}
