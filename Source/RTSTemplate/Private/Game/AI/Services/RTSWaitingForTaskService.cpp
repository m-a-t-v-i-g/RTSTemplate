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

}
