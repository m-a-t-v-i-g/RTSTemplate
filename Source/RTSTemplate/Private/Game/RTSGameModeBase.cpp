// Real Time Strategy C++ template by matvig.

#include "Game/RTSGameModeBase.h"
#include "Game/RTSCameraPawn.h"
#include "Game/RTSHUD.h"
#include "Game/RTSPlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ARTSGameModeBase::ARTSGameModeBase()
{
	DefaultPawnClass = nullptr;

	HUDClass = ARTSHUD::StaticClass();
	
	PlayerControllerClass = ARTSPlayerController::StaticClass();

	GameStateClass = AGameStateBase::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> BP_RTSCameraPawn(TEXT("/Game/Game/Player/BP_RTSCameraPawn"));
	if (BP_RTSCameraPawn.Class != nullptr)
	{
		CameraPawn = BP_RTSCameraPawn.Class;
	}
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
	
	auto SpawnPawn = GetWorld()->SpawnActor<ARTSCameraPawn>(CameraPawn, SpawnTransform(), SpawnParameters);
	if (SpawnPawn)
	{
		PlayerController->Possess(SpawnPawn);
		SpawnPawn->InitInputs();
		SpawnPawn->InitHUD();
	}
}
