// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RTSRefreshTaskTask.generated.h"

UCLASS()
class RTSTEMPLATE_API URTSRefreshTaskTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URTSRefreshTaskTask();
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CurrentTaskKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
