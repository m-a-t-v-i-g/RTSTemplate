// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSTypes.h"
#include "RTSAIController.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSAIController : public AAIController
{
	GENERATED_BODY()
public:
	ARTSAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	void MoveToDestination();
	void LookAtDestination();
};
