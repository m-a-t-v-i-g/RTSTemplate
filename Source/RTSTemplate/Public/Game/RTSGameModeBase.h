// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "RTSTypes.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameModeBase.generated.h"

class ARTSCameraPawn;

UCLASS()
class RTSTEMPLATE_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARTSGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
	FGameData GameSettings;
	
protected:
	FTransform SpawnTransform();

public:
	void SpawnPlayer(APlayerController* PlayerController);
	void AssignPlayer(APlayerController* PlayerController, ARTSCameraPawn* PlayerPawn);
	
};
