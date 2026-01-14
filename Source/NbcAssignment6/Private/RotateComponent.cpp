#include "RotateComponent.h"

URotateComponent::URotateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URotateComponent::SetRotationActive(bool bActive) const
{
	if (bActive)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(RotateTimerHandle);
		GetWorld()->GetTimerManager().UnPauseTimer(ReverseEventTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().PauseTimer(RotateTimerHandle);
		GetWorld()->GetTimerManager().PauseTimer(ReverseEventTimerHandle);
	}
}

void URotateComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdatesPerSecond = UpdatesPerSecond > 0.0f ? UpdatesPerSecond : 60.0f;
	ActualInterval = 1.0f / UpdatesPerSecond;
	
	GetWorld()->GetTimerManager().SetTimer(
		RotateTimerHandle,
		this,
		&URotateComponent::UpdateRotation,
		ActualInterval,
		true
	);
	
	GetWorld()->GetTimerManager().SetTimer(
		ReverseEventTimerHandle,
		this,
		&URotateComponent::ReverseRotation,
		ReverseEventFrequency,
		true
	);
}

void URotateComponent::UpdateRotation() const
{
	if (AActor* Owner = GetOwner())
	{
		Owner->AddActorLocalRotation(RotationSpeed * ActualInterval);
	}
}

void URotateComponent::ReverseRotation()
{
	if (!bReverseEventOn) { return; }
	
	RotationSpeed *= -1.0f;
}
