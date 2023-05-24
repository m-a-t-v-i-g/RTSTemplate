// Real Time Strategy C++ template by matvig.

#include "Game/RTSPlayerController.h"
#include "Game/RTSGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController()) return;

	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	ServerSpawnPlayer();
}

void ARTSPlayerController::ServerSpawnPlayer_Implementation()
{
	if (!GetWorld()) return;
	
	auto GetGameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (!GetGameMode) return;
	
	auto GetRTSGameMode = Cast<ARTSGameModeBase>(GetGameMode);
	if (GetRTSGameMode)
	{
		GetRTSGameMode->SpawnPlayer(this);
	}
}
