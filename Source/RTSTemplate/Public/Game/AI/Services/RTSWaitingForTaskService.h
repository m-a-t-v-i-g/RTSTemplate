// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "RTSTypes.h"
#include "BehaviorTree/BTService.h"
#include "RTSWaitingForTaskService.generated.h"

UCLASS()
class RTSTEMPLATE_API URTSWaitingForTaskService : public UBTService
{
	GENERATED_BODY()
	
public:
	URTSWaitingForTaskService();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CurrentTaskKey;

	EUnitCurrentTask CurrentTask;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
