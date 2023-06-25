// Real Time Strategy C++ template by matvig.

#include "Game/RTSHUD.h"

#include "Blueprint/UserWidget.h"
#include "Game/RTSPlayerState.h"
#include "Kismet/KismetStringLibrary.h"
#include "Widgets/RTSHUDWidget.h"

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bSelecting)
	{
		DrawRectangle();
	}
	else
	{
		FoundUnitByCursor();
	}
	DebugMessage();
}

FVector2D ARTSHUD::GetMousePosition()
{
	auto GetOwner = GetOwningPlayerController();
	if (!GetOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid player controller."));
		return FVector2D(0.0,0.0);
	}

	float MousePosX, MousePosY;
	GetOwner->GetMousePosition(MousePosX, MousePosY);

	return FVector2D(MousePosX, MousePosY);
}

void ARTSHUD::InitWidgets(TSubclassOf<URTSHUDWidget> Widget)
{
	auto CreateHUDWidget = CreateWidget<URTSHUDWidget>(GetOwningPlayerController(), Widget);
	if (CreateHUDWidget)
	{
		HUDWidget = CreateHUDWidget;
	}
	if (!HUDWidget->IsInViewport())
	{
		HUDWidget->AddToViewport();
	}
}

void ARTSHUD::StartSelecting()
{
	if (SelectedUnits.Num() > 0)
	{
		for (auto SelectedUnit : SelectedUnits)
		{
			for (auto UnitInCursor : CursorUnits)
			{
				if (SelectedUnit != UnitInCursor)
				{
					if (IsValidPlayerID(Cast<AActor>(UnitInCursor)))
					{
						PossibleUnits.AddUnique(UnitInCursor);
						return;
					}
				}
			}
		}
	}
	if (FoundUnitByCursor())
	{
		auto FoundUnits = GetUnitsInCursor();
		for (auto FoundUnit : FoundUnits)
		{
			if (IsValidPlayerID(FoundUnit))
			{
				auto TempUnit = Cast<IRTSUnitInterface>(FoundUnit);
				if (TempUnit)
				{
					if (!SelectedUnits.Contains(TempUnit))
					{
						PossibleUnits.AddUnique(TempUnit);
					}
				}
			}
		}
		return;
	}

	bSelecting = true;
	InitialPoint = GetMousePosition();

	ClearSelectedUnits();
}

void ARTSHUD::StopSelecting()
{
	bSelecting = false;

	UpdateSelectedUnits();
}

bool ARTSHUD::FoundUnitByCursor()
{
	FHitResult HitResult;
	
	GetOwningPlayerController()->GetHitResultUnderCursorByChannel(TraceTypeQuery6, false, HitResult);
	
	auto GetHitResult = HitResult.GetActor();
	if (GetHitResult)
	{
		auto UnitInterface = Cast<IRTSUnitInterface>(GetHitResult);
		if (UnitInterface)
		{
			UnitInterface->SetUnitIsFound(true);
			CursorUnits.AddUnique(UnitInterface);
			return true;
		}
		if (!UnitInterface && CursorUnits.Num() > 0)
		{
			for (int i = 0; i < CursorUnits.Num(); i++)
			{
				CursorUnits[i]->SetUnitIsFound(false);
				CursorUnits.RemoveAt(i);
			}
			return false;
		}
	}
	return false;
}

void ARTSHUD::FoundUnitsInRect(FVector2D FirstPoint, FVector2D SecondPoint)
{
	TArray<AActor*> FoundUnits;
	auto GetUnitsInRect = GetUnitsInSelectionRectangle<AActor>(FirstPoint, SecondPoint, FoundUnits, false, false);
	if (GetUnitsInRect)
	{
		for (auto FoundUnit : FoundUnits)
		{
			if (IsValidPlayerID(FoundUnit))
			{
				auto TempUnit = Cast<IRTSUnitInterface>(FoundUnit);
				if (TempUnit)
				{
					if (!PossibleUnits.Contains(TempUnit))
					{
						TempUnit->SetUnitIsFound(true);
						PossibleUnits.AddUnique(TempUnit);
					}
				}
			}
		}
		for (int i = 0; i < PossibleUnits.Num(); i++)
		{
			auto TempUnit = PossibleUnits[i];
			if (TempUnit)
			{
				if (!FoundUnits.Contains(Cast<AActor>(TempUnit)))
				{
					TempUnit->SetUnitIsFound(false);
					PossibleUnits.RemoveAt(i);
				}
			}
		}
	}
}

bool ARTSHUD::IsValidPlayerID(AActor* Unit)
{
	auto PlayerState = Cast<ARTSPlayerState>(GetOwningPlayerController()->PlayerState);
	if (!PlayerState) return false;
	
	auto TempUnit = Cast<IRTSUnitInterface>(Unit);
	if (!TempUnit) return false;
	
	if (PlayerState->GetPlayerID() == TempUnit->GetUnitPlayerID())
	{
		return true;
	}
	return false;
}

TArray<AActor*> ARTSHUD::GetUnitsInCursor()
{
	TArray<AActor*> TempActors;
	if (CursorUnits.Num() > 0)
	{
		for (auto UnitInCursor : CursorUnits)
		{
			auto TempUnit = Cast<AActor>(UnitInCursor);
			TempActors.AddUnique(TempUnit);
		}
	}
	return TempActors;
}

void ARTSHUD::UpdateSelectedUnits()
{
	if (PossibleUnits.Num() > 0)
	{
		TArray<AActor*> TempActors;
		for (auto UnitInRect : PossibleUnits)
		{
			auto TempUnit = Cast<AActor>(UnitInRect);
			if (IsValid(TempUnit))
			{
				UnitInRect->SetUnitIsFound(false);
				UnitInRect->SetUnitIsSelected(true);
				TempActors.AddUnique(TempUnit);
			}
		}
		SelectedUnits = PossibleUnits;
		PossibleUnits.Empty();

		OnUpdateSelectedUnits.Broadcast(TempActors);
	}
}

void ARTSHUD::ClearSelectedUnits()
{
	if (SelectedUnits.Num() > 0)
	{
		TArray<AActor*> TempActors;
		for (auto SelectedUnit : SelectedUnits)
		{
			if (CursorUnits.Contains(SelectedUnit))
			{
				return;
			}
		}
		for (auto SelectedUnit : SelectedUnits)
		{
			auto TempUnit = Cast<AActor>(SelectedUnit);
			if (IsValid(TempUnit))
			{
				SelectedUnit->SetUnitIsSelected(false);
				TempActors.Empty();
			}
		}
		SelectedUnits.Empty();
		
		OnUpdateSelectedUnits.Broadcast(TempActors);
	}
	CursorUnits.Empty();
}

void ARTSHUD::DrawRectangle_Implementation()
{
	CurrentPoint = GetMousePosition();
	DrawRect(FLinearColor(0, 0, 0.1, 0.15), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
	FoundUnitsInRect(InitialPoint, CurrentPoint);
}

void ARTSHUD::DebugMessage_Implementation()
{
	FString UnitsInCursorNum = UKismetStringLibrary::Conv_IntToString(CursorUnits.Num());
	FString UnitsInCursorNumMessage = FString::Printf(TEXT("Units by cursor found: ")) + UnitsInCursorNum;
	GEngine->AddOnScreenDebugMessage(102, 1.5, FColor::Yellow, UnitsInCursorNumMessage);

	FString UnitsInRectNum = UKismetStringLibrary::Conv_IntToString(PossibleUnits.Num());
	FString UnitsInRectNumMessage = FString::Printf(TEXT("Possible units: ")) + UnitsInRectNum;
	GEngine->AddOnScreenDebugMessage(101, 1.5, FColor::Yellow, UnitsInRectNumMessage);

	FString UnitsNum = UKismetStringLibrary::Conv_IntToString(SelectedUnits.Num());
	FString UnitsNumMessage = FString::Printf(TEXT("Units are selected: ")) + UnitsNum;
	GEngine->AddOnScreenDebugMessage(100, 1.5, FColor::Yellow, UnitsNumMessage);
}
