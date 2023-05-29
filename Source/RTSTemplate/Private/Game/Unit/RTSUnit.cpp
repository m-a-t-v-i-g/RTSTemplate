// Real Time Strategy C++ template by matvig.

#include "Game/Unit/RTSUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ARTSUnit::ARTSUnit()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARTSUnit::SetUnitIsFound(bool IsFound)
{
	bIsFound = IsFound;
	if (IsFound)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.5, FColor::Green, TEXT("Found"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(5, 1.5, FColor::Green, TEXT("Not found"));
	}
	return IsFound;
}

bool ARTSUnit::SetUnitIsSelected(bool IsSelected)
{
	bIsSelected = IsSelected;
	if (IsSelected)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.5, FColor::Green, TEXT("Selected"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(5, 1.5, FColor::Green, TEXT("Deselected"));
	}
	return IsSelected;
}

void ARTSUnit::MoveToDestination()
{
	ServerMoveToLocation();
}

void ARTSUnit::ServerMoveToLocation_Implementation()
{
	if (!GetMovementComponent()) return;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), CachedDestination);
}
