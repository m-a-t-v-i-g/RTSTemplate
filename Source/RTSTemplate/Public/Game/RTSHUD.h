// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/RTSUnitInterface.h"
#include "RTSHUD.generated.h"

class ARTSPlayerController;
class ARTSUnit;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSelectedUnits, const TArray<AActor*>&)

UCLASS()
class RTSTEMPLATE_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	TArray<IRTSUnitInterface*> CursorUnits;
	TArray<IRTSUnitInterface*> PossibleUnits;
	TArray<IRTSUnitInterface*> SelectedUnits;
	
	FVector2D InitialPoint;
	FVector2D CurrentPoint;

	bool bSelecting = false;

	FOnUpdateSelectedUnits OnUpdateSelectedUnits;
	
	FVector2D GetMousePosition();
	
	void StartSelecting();
	void StopSelecting();
	
	bool FoundUnitByCursor();
	void FoundUnitsInRect(FVector2D FirstPoint, FVector2D SecondPoint);

	bool IsValidPlayerID(AActor* Unit);
	
	TArray<AActor*> GetUnitsInCursor();
	
	void UpdateSelectedUnits();
	void ClearSelectedUnits();
	
	void DebugUnits();
	
	UFUNCTION(Client, Reliable)
	void DrawRectangle();

	UFUNCTION(Client, Reliable)
	void DebugMessage();

protected:
	template <typename ClassFilter>
	bool GetUnitsInSelectionRectangle(const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<ClassFilter*>& OutActors, bool bIncludeNonCollidingComponents = true, bool bActorMustBeFullyEnclosed = false)
	{
		if (!ClassFilter::StaticClass()->IsChildOf(AActor::StaticClass()))
		{
			return false;
		}

		TArray<AActor*> OutActorsBaseArray;
		GetActorsInSelectionRectangle(ClassFilter::StaticClass(), FirstPoint, SecondPoint, OutActorsBaseArray, bIncludeNonCollidingComponents, bActorMustBeFullyEnclosed);

		for (AActor* EachActor : OutActorsBaseArray)
		{
			if (EachActor->GetClass()->ImplementsInterface(URTSUnitInterface::StaticClass()))
			{
				OutActors.Add(CastChecked<ClassFilter>(EachActor));
			}
		}

		return true;
	}
};
