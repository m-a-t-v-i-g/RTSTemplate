// Real Time Strategy C++ template by matvig.

#include "Game/AI/Services/RTSWaitingForTaskService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/RTSUnitInterface.h"

URTSWaitingForTaskService::URTSWaitingForTaskService()
{
	NodeName = "Waiting For Task";
}

void URTSWaitingForTaskService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		if (Controller)
		{
			const auto Pawn = Cast<IRTSUnitInterface>(Controller->GetPawn());
			if (Pawn)
			{
				if (Pawn->CurrentTask == EUnitCurrentTask::Idle)
				{
					Blackboard->SetValueAsName(CurrentTaskKey.SelectedKeyName, "Idle");
					GEngine->AddOnScreenDebugMessage(3, 1.5, FColor::Cyan, TEXT("Value: Idle"));
				}
				if (Pawn->CurrentTask == EUnitCurrentTask::MoveToDestination)
				{
					Blackboard->SetValueAsName(CurrentTaskKey.SelectedKeyName, "MoveToDestination");
					GEngine->AddOnScreenDebugMessage(3, 1.5, FColor::Cyan, TEXT("Value: Move to destination"));
				}
				if (Pawn->CurrentTask == EUnitCurrentTask::LookAtDestination)
				{
					Blackboard->SetValueAsName(CurrentTaskKey.SelectedKeyName, "LookAtDestination");
					GEngine->AddOnScreenDebugMessage(3, 1.5, FColor::Cyan, TEXT("Value: Look at destination"));
				}
			}
		}
	}
}
