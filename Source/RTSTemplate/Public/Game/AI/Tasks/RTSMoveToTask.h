// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RTSMoveToTask.generated.h"

UCLASS()
class RTSTEMPLATE_API URTSMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URTSMoveToTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector MoveToKey;
	
};
