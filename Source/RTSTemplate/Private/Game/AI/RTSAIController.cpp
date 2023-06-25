// Real Time Strategy C++ template by matvig.

#include "Game/AI/RTSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/RTSUnitInterface.h"
#include "Navigation/CrowdFollowingComponent.h"

ARTSAIController::ARTSAIController(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
}

void ARTSAIController::BeginPlay()
{
	Super::BeginPlay();

	
	if (GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Owner: %s"), *GetName(), *GetOwner()->GetName());
	}
	
	if (GetPawn())
	{
		auto ControlledUnit = Cast<IRTSUnitInterface>(GetPawn());
		if (ControlledUnit)
		{
			SetPlayerID(ControlledUnit->GetUnitPlayerID());
			SetTeamID(ControlledUnit->GetUnitTeamID());
		}
		UE_LOG(LogTemp, Warning, TEXT("[%s] Pawn: %s"), *GetName(), *GetPawn()->GetName());
	}
}

void ARTSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ARTSAIController::MoveToDestination()
{
	if (!GetBlackboardComponent()) return;
	GetBlackboardComponent()->SetValueAsBool("MoveTo", true);
}

void ARTSAIController::LookAtDestination()
{
	if (!GetBlackboardComponent()) return;
	GetBlackboardComponent()->SetValueAsBool("LookAt", true);
}

void ARTSAIController::SetPlayerID_Implementation(int NewPlayerID)
{
	PlayerID = NewPlayerID;
}

void ARTSAIController::SetTeamID_Implementation(int NewTeamID)
{
	TeamID = NewTeamID;
}