// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RTSLookAtTask.generated.h"

UCLASS()
class RTSTEMPLATE_API URTSLookAtTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URTSLookAtTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector LookAtKey;
	
};
