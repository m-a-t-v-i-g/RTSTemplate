// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSTypes.h"
#include "RTSHumanAIController.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSHumanAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARTSHumanAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	EUnitCurrentTask CurrentTask = EUnitCurrentTask::Idle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName CurrentTaskKeyName;

	virtual void Tick(float DeltaSeconds) override;

	EUnitCurrentTask GetCurrentTask();
};
