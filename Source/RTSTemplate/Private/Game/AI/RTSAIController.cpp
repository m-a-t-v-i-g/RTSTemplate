// Real Time Strategy C++ template by matvig.

#include "Game/AI/RTSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

ARTSAIController::ARTSAIController(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
}

void ARTSAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) return;
	UE_LOG(LogTemp, Warning, TEXT("Pawn: %s"), *GetPawn()->GetName());

	if (!GetOwner()) return;
	UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *GetOwner()->GetName());
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
