#include "BasePlatform.h"

#include "RotateComponent.h"
#include "ShuttleMoveComponent.h"

ABasePlatform::ABasePlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRootComponent);

	ShuttleMoveComponent = CreateDefaultSubobject<UShuttleMoveComponent>(TEXT("ShuttleMoveComponent"));
	RotateComponent = CreateDefaultSubobject<URotateComponent>(TEXT("RotateComponent"));
}

void ABasePlatform::InitRandom() const
{
	int32 ActionType = FMath::RandRange(0, 2);
	const bool bWillMove = (ActionType == 0 || ActionType == 2);
	const bool bWillRotate = (ActionType == 1 || ActionType == 2);

	if (ShuttleMoveComponent)
	{
		ShuttleMoveComponent->SetMovementActive(bWillMove);
		if (bWillMove)
		{
			ShuttleMoveComponent->Velocity = FMath::RandRange(300.f, 1000.f);
			float RandomDist = FMath::RandRange(700.f, 1500.f);
			int32 RandomAxis = FMath::RandRange(0, 2);

			FVector NewRange = FVector::ZeroVector;

			switch (RandomAxis)
			{
			case 0:
				NewRange.X = RandomDist;
				break;
			case 1:
				NewRange.Y = RandomDist;
				break;
			case 2:
				NewRange.Z = RandomDist;
				break;
			default:
				NewRange.X = RandomDist;
				break;
			}

			ShuttleMoveComponent->MaxRange = NewRange;
		}
	}

	if (RotateComponent)
	{
		RotateComponent->SetRotationActive(bWillRotate);
		if (bWillRotate)
		{
			RotateComponent->RotationSpeed = FRotator(0, FMath::RandRange(-150.f, 150.f), 0);
		}
	}
}

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
}
