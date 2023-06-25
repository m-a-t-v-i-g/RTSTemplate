// Real Time Strategy C++ template by matvig.

#include "Game/AI/Tasks/RTSMoveToTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interfaces/RTSUnitInterface.h"

URTSMoveToTask::URTSMoveToTask()
{
	NodeName = "Move To";
}

EBTNodeResult::Type URTSMoveToTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Cast<IRTSUnitInterface>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Pawn->GetDestination());
	Blackboard->SetValueAsBool("MoveTo", false);
	return EBTNodeResult::Succeeded;
}
