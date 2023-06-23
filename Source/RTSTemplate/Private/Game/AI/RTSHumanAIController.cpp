// Real Time Strategy C++ template by matvig.

#include "Game/AI/RTSHumanAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

ARTSHumanAIController::ARTSHumanAIController(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
}

void ARTSHumanAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

EUnitCurrentTask ARTSHumanAIController::GetCurrentTask()
{
	return EUnitCurrentTask::Idle;
}

