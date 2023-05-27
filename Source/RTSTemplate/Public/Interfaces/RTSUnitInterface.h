// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSUnitInterface.generated.h"

UINTERFACE(MinimalAPI)
class URTSUnitInterface : public UInterface
{
	GENERATED_BODY()
};

class RTSTEMPLATE_API IRTSUnitInterface
{
	GENERATED_BODY()

public:
	bool bIsFound = false;
	bool bIsSelected = false;
	
	FVector LocationToMove;
	
	virtual bool SetUnitIsFound(bool SetFound);
	virtual bool SetUnitIsSelected(bool SetSelected);

	bool CanBeFound();
	bool CanBeSelected();

	virtual void MoveToLocation();
};
