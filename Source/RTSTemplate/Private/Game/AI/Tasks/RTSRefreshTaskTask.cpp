// Real Time Strategy C++ template by matvig.

#include "Game/AI/Tasks/RTSRefreshTaskTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/RTSUnitInterface.h"

URTSRefreshTaskTask::URTSRefreshTaskTask()
{
	NodeName = "Refresh Task";
}

EBTNodeResult::Type URTSRefreshTaskTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Cast<IRTSUnitInterface>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	Pawn->CurrentTask = EUnitCurrentTask::Idle;
	
	Blackboard->SetValueAsName(CurrentTaskKey.SelectedKeyName, "Idle");
	return EBTNodeResult::Succeeded;
}
