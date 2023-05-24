// Real Time Strategy C++ template by matvig.

#include "Game/Unit/RTSUnit.h"

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

void ARTSUnit::SetFound()
{
	UnitFound = true;
	GEngine->AddOnScreenDebugMessage(4, 1.5, FColor::Green, TEXT("Found"));
}

void ARTSUnit::SetNotFound()
{
	UnitFound = false;
	GEngine->AddOnScreenDebugMessage(4, 1.5, FColor::Red, TEXT("Not found"));
}

void ARTSUnit::SetSelected()
{
	UnitIsSelected = true;
	GEngine->AddOnScreenDebugMessage(4, 1.5, FColor::Green, TEXT("Selected"));
}

void ARTSUnit::SetDeselected()
{
	UnitIsSelected = false;
	GEngine->AddOnScreenDebugMessage(4, 1.5, FColor::Red, TEXT("Deselected"));
}

bool ARTSUnit::CanBeFound()
{
	return !UnitIsSelected;
}

bool ARTSUnit::CanBeSelected()
{
	return CanBeFound();
}

void ARTSUnit::MoveToLocation_Implementation()
{
	
}
