// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameModeBase.generated.h"

class ARTSCameraPawn;

UCLASS()
class RTSTEMPLATE_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARTSGameModeBase();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
	TSubclassOf<ARTSCameraPawn> CameraPawn;

	FTransform SpawnTransform();

public:
	void SpawnPlayer(APlayerController* PlayerController);
	
};
