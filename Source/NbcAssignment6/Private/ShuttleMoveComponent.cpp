#include "ShuttleMoveComponent.h"

UShuttleMoveComponent::UShuttleMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShuttleMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		StartLocation = Owner -> GetActorLocation();
	}
	
	UpdatesPerSecond = UpdatesPerSecond > 0.0f ? UpdatesPerSecond : 60.0f;
	ActualInterval = 1.0f / UpdatesPerSecond;
	
	GetWorld()->GetTimerManager().SetTimer(
		MoveTimerHandle,
		this,
		&UShuttleMoveComponent::UpdateMovement,
		ActualInterval,
		true
	);
}

bool UShuttleMoveComponent::IsMovingReverse() const
{
	return Direction <= 0.0f;
}

void UShuttleMoveComponent::UpdateMovement()
{
	AActor* Owner = GetOwner();
	if (!Owner) { return; }
	
	FVector CurrentLocation = Owner->GetActorLocation();
	FVector TargetDestination = IsMovingReverse() ? StartLocation : StartLocation + MaxRange;
	
	FVector MoveNormal = (TargetDestination - CurrentLocation).GetSafeNormal();
	CurrentLocation += MoveNormal * Velocity * ActualInterval;
	Owner->SetActorLocation(CurrentLocation);

	if (FVector::Dist(CurrentLocation, TargetDestination) <= (Velocity * ActualInterval))
	{
		Owner->SetActorLocation(TargetDestination);
		Direction *= -1.0f;
	}
}

void UShuttleMoveComponent::SetMovementActive(bool bActive) const
{
	if (bActive)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(MoveTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().PauseTimer(MoveTimerHandle);
	}
}
