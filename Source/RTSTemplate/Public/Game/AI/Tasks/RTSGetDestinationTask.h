// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RTSGetDestinationTask.generated.h"

UCLASS()
class RTSTEMPLATE_API URTSGetDestinationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URTSGetDestinationTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector DestinationKey;
	
};
