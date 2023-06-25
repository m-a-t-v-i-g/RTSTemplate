// Real Time Strategy C++ template by matvig.

#include "Game/RTSPlayerState.h"
#include "Kismet/GameplayStatics.h"

void ARTSPlayerState::BeginPlay()
{
	Super::BeginPlay();

}

void ARTSPlayerState::SetPlayerID_Implementation(int ID)
{
	PlayerID = ID;
}

void ARTSPlayerState::SetTeamID_Implementation(int ID)
{
	TeamID = ID;
}
