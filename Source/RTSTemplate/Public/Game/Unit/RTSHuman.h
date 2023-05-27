// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
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
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
