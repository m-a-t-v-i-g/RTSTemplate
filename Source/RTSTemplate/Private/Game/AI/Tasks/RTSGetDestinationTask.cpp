// Real Time Strategy C++ template by matvig.

#include "Game/AI/Tasks/RTSGetDestinationTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/RTSUnitInterface.h"

URTSGetDestinationTask::URTSGetDestinationTask()
{
	NodeName = "Get Destination";
}

EBTNodeResult::Type URTSGetDestinationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Cast<IRTSUnitInterface>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(DestinationKey.SelectedKeyName, Pawn->CachedDestination);
	return EBTNodeResult::Succeeded;
}

