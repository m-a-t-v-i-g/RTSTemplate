// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/RTSUnitInterface.h"
#include "RTSUnit.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSUnit : public ACharacter, public IRTSUnitInterface
{
	GENERATED_BODY()
	
public:	
	ARTSUnit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual bool SetUnitIsFound(bool IsFound) override;
	virtual bool SetUnitIsSelected(bool IsSelected) override;

	virtual void MoveToLocation() override;

	UFUNCTION(Server, Reliable)
	void ServerMoveToLocation();
};
