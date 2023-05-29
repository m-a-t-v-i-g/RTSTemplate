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
	
	UPROPERTY(EditInstanceOnly, Category = "Unit")
	FUnit Unit; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Human")
	FHuman Human;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual int GetUnitPlayerID() override;
	
	virtual bool SetUnitIsFound(bool IsFound) override;
	virtual bool SetUnitIsSelected(bool IsSelected) override;

	virtual void MoveToDestination() override;

};
