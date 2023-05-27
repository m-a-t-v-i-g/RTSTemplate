// Real Time Strategy C++ template by matvig.

#include "Game/Unit/RTSHuman.h"

ARTSHuman::ARTSHuman()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARTSHuman::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTSHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTSHuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
