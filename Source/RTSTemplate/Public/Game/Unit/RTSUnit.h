// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSUnit.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSUnit : public APawn
{
	GENERATED_BODY()
	
public:	
	ARTSUnit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	bool UnitFound = false;
	bool UnitIsSelected = false;

	FVector LocationToMove;
	
	void SetFound();
	void SetNotFound();
	
	void SetSelected();
	void SetDeselected();

	bool CanBeFound();
	bool CanBeSelected();
	
	UFUNCTION(Server, Reliable)
	void MoveToLocation();
};
