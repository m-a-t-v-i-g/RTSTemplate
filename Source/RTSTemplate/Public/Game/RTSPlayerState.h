// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RTSPlayerState.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	int PlayerID;
	int TeamID;

public:
	int GetPlayerID() const { return PlayerID; }
	int GetTeamID() const { return TeamID; }
	
	UFUNCTION(NetMulticast, Reliable)
	void SetPlayerID(int ID);

	UFUNCTION(NetMulticast, Reliable)
	void SetTeamID(int ID);

};
