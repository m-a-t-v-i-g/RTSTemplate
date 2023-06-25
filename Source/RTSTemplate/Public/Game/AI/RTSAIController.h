// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSAIController.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARTSAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
private:
	int PlayerID = 1;
	int TeamID = 1;
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	int GetPlayerID() { return PlayerID; }
	int GetTeamID() { return TeamID; }
	
	void MoveToDestination();
	void LookAtDestination();

	UFUNCTION(NetMulticast, Reliable)
	void SetPlayerID(int NewPlayerID);

	UFUNCTION(NetMulticast, Reliable)
	void SetTeamID(int NewTeamID);
};
