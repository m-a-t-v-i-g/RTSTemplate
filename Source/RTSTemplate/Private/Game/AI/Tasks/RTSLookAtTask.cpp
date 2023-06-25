// Real Time Strategy C++ template by matvig.

#include "Game/AI/Tasks/RTSLookAtTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/RTSUnitInterface.h"

URTSLookAtTask::URTSLookAtTask()
{
	NodeName = "Look At";
}

EBTNodeResult::Type URTSLookAtTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;
	
	const auto Pawn = Cast<IRTSUnitInterface>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;
	
	Controller->SetFocalPoint(Pawn->GetDestination());
	Blackboard->SetValueAsBool("LookAt", false);

	UE_LOG(LogTemp, Warning, TEXT("%f"), Pawn->GetDestination().Rotation().Yaw);
	return EBTNodeResult::Succeeded;
}

