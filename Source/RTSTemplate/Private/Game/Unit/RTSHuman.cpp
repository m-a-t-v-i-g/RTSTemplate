// Real Time Strategy C++ template by matvig.

#include "Game/Unit/RTSHuman.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

ARTSHuman::ARTSHuman()
{
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0, 300.0, 0.0);

	Unit.PlayerID = 1;
	Unit.TeamID = 1;

	PrimaryActorTick.bCanEverTick = true;

}

void ARTSHuman::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTSHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTSHuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ARTSHuman::GetUnitPlayerID()
{
	return Unit.PlayerID;
}

int ARTSHuman::GetUnitTeamID()
{
	return Unit.TeamID;
}

bool ARTSHuman::SetUnitIsFound(bool IsFound)
{
	bIsFound = IsFound;
	return IsFound;
}

bool ARTSHuman::SetUnitIsSelected(bool IsSelected)
{
	bIsSelected = IsSelected;
	return IsSelected;
}

void ARTSHuman::MoveToDestination()
{
	if (!GetMovementComponent()) return;

	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), CachedDestination);
}
