// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "RTSTypes.h"
#include "GameFramework/Character.h"
#include "Interfaces/RTSUnitInterface.h"
#include "RTSHuman.generated.h"

UCLASS()
class RTSTEMPLATE_API ARTSHuman : public ACharacter, public IRTSUnitInterface
{
	GENERATED_BODY()

public:
	ARTSHuman();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Unit")
	FUnit Unit; 

	UPROPERTY(EditAnywhere, Category = "Human")
	FHuman Human;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual int GetUnitPlayerID() override;
	virtual int GetUnitTeamID() override;
	
	virtual bool SetUnitIsFound(bool IsFound) override;
	virtual bool SetUnitIsSelected(bool IsSelected) override;
};
