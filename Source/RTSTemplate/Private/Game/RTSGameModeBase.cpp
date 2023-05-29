// Real Time Strategy C++ template by matvig.

#include "Game/RTSGameModeBase.h"
#include "Game/RTSCameraPawn.h"
#include "Game/RTSHUD.h"
#include "Game/RTSPlayerController.h"
#include "Game/RTSPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ARTSGameModeBase::ARTSGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> BP_RTSCameraPawn(TEXT("/Game/Game/Player/BP_RTSCameraPawn"));
	if (BP_RTSCameraPawn.Class != nullptr)
	{
		DefaultPawnClass = BP_RTSCameraPawn.Class;
	}
	
	HUDClass = ARTSHUD::StaticClass();
	
	PlayerControllerClass = ARTSPlayerController::StaticClass();

	GameStateClass = AGameStateBase::StaticClass();

	PlayerStateClass = ARTSPlayerState::StaticClass();
}

FTransform ARTSGameModeBase::SpawnTransform()
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	auto RandomInteger = UKismetMathLibrary::RandomIntegerInRange(0, PlayerStarts.Num() - 1);
	auto GetRandomStartPoint = PlayerStarts[RandomInteger];
	
	auto StartTransform = GetRandomStartPoint->GetActorTransform();
	
	return StartTransform;
}

void ARTSGameModeBase::SpawnPlayer(APlayerController* PlayerController)
{
	if (!GetWorld()) return;
	if (!PlayerController) return;
	
	auto GetControlledPawn = PlayerController->GetPawn();
	if (IsValid(GetControlledPawn)) GetControlledPawn->Destroy();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = PlayerController;
	
	auto SpawnPawn = GetWorld()->SpawnActor<ARTSCameraPawn>(DefaultPawnClass, SpawnTransform(), SpawnParameters);
	if (SpawnPawn)
	{
		PlayerController->Possess(SpawnPawn);
		SpawnPawn->InitInputs();
		SpawnPawn->InitHUD();

		AssignPlayer(PlayerController, SpawnPawn);
	}
}

void ARTSGameModeBase::AssignPlayer(APlayerController* PlayerController, ARTSCameraPawn* PlayerPawn)
{
	if (!PlayerController || !PlayerPawn) return;
	
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), AllPlayers);

	const auto PlayerState = Cast<ARTSPlayerState>(PlayerController->PlayerState);
	if (!PlayerState) return;
	
	const auto PlayerIndex = AllPlayers.Find(PlayerController) + 1;
	
	PlayerState->SetPlayerID(PlayerIndex);
	PlayerState->SetTeamID(PlayerIndex); // данный ID временный
	
	PlayerPawn->SetPlayerID(PlayerIndex);
	PlayerPawn->SetTeamID(PlayerIndex); // данный ID временный
}
