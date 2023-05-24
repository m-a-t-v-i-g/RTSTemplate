// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

class ARTSPlayerController;
class ARTSUnit;

UCLASS()
class RTSTEMPLATE_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;
	
	TSubclassOf<ARTSUnit> Unit;
	
	TArray<ARTSUnit*> UnitsInCursor;
	TArray<ARTSUnit*> UnitsInRect;
	TArray<ARTSUnit*> SelectedUnits;

	FVector2D GetMousePosition();
	
	FVector2D InitialPoint;
	FVector2D CurrentPoint;

	bool bSelecting = false;
	
	void StartSelecting();
	void StopSelecting();
	
	void FoundUnitByCursor();
	void FoundUnitsInRect(FVector2D FirstPoint, FVector2D SecondPoint);

	void UpdateSelectedUnits();
	void ClearSelectedUnits();

	UFUNCTION(Client, Reliable)
	void DrawRectangle();

	UFUNCTION(Client, Reliable)
	void DebugMessage();
};
