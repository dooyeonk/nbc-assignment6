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

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
}
