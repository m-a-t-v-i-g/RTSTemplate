// Real Time Strategy C++ template by matvig.

#include "Game/RTSHUD.h"
#include "Game/RTSCameraPawn.h"
#include "Game/Unit/RTSUnit.h"
#include "Kismet/KismetStringLibrary.h"

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

void ARTSHUD::StartSelecting()
{
	bSelecting = true;
	InitialPoint = GetMousePosition();

	
}

void ARTSHUD::StopSelecting()
{
	bSelecting = false;
}

void ARTSHUD::FoundUnitByCursor()
{
	FHitResult HitResult;
	
	GetOwningPlayerController()->GetHitResultUnderCursorByChannel(TraceTypeQuery6, false, HitResult);

	auto GetHitResult = HitResult.GetActor();
	if (GetHitResult)
	{
		auto GetHitActor = GetHitResult->IsA(ARTSUnit::StaticClass());
		auto GetHitUnit = Cast<ARTSUnit>(GetHitResult);
		if (GetHitActor)
		{
			if (!UnitsInCursor.Contains(GetHitUnit) && GetHitUnit->CanBeFound())
			{
				GetHitUnit->SetFound();
				UnitsInCursor.AddUnique(GetHitUnit);
			}
		}
		else if (!GetHitActor && UnitsInCursor.Num() > 0)
		{
			for (int i = 0; i < UnitsInCursor.Num(); ++i)
			{
				if (!UnitsInCursor[i]->UnitIsSelected)
				{
					UnitsInCursor[i]->SetNotFound();
					UnitsInCursor.RemoveAt(i);
				}
			}
		}
	}
}

void ARTSHUD::FoundUnitsInRect(FVector2D FirstPoint, FVector2D SecondPoint)
{
	TArray<ARTSUnit*> FoundUnits;
	
	auto GetUnitsInRect = GetActorsInSelectionRectangle<ARTSUnit>(FirstPoint, SecondPoint, FoundUnits, false, false);
	if (GetUnitsInRect)
	{
		for (int i = 0; i < FoundUnits.Num(); ++i)
		{
			if (!UnitsInRect.Contains(FoundUnits[i]))
			{
				if (FoundUnits.IsValidIndex(i))
				{
					FoundUnits[i]->SetFound();
					UnitsInRect.AddUnique(FoundUnits[i]);
				}
			}
		}
		for (int i = 0; i < UnitsInRect.Num(); ++i)
		{
			if (!FoundUnits.Contains(UnitsInRect[i]))
			{
				if (UnitsInRect.IsValidIndex(i))
				{
					UnitsInRect[i]->SetNotFound();
					UnitsInRect.RemoveAt(i);
				}
			}
		}
	}
}

void ARTSHUD::UpdateSelectedUnits()
{
	if (UnitsInRect.Num() > 0)
	{
		auto CameraPawn = Cast<ARTSCameraPawn>(GetOwningPawn());
		for (auto UnitInRect : UnitsInRect)
		{
			if (IsValid(UnitInRect))
			{
				if (UnitInRect->UnitIsSelected) return;
				
				UnitInRect->SetNotFound();
				UnitInRect->SetSelected();
			}
		}
		SelectedUnits = UnitsInRect;
		UnitsInRect.Empty();

		CameraPawn->GetSelectedUnits();
	}
}

void ARTSHUD::ClearSelectedUnits()
{
	if (SelectedUnits.Num() > 0)
	{
		auto CameraPawn = Cast<ARTSCameraPawn>(GetOwningPawn());
		for (auto SelectedUnit : SelectedUnits)
		{
			if (IsValid(SelectedUnit))
			{
				if (SelectedUnit->UnitIsSelected)
				{
					SelectedUnit->SetDeselected();
				}
			}
		}
		SelectedUnits.Empty();

		CameraPawn->GetSelectedUnits();
		
		//GEngine->AddOnScreenDebugMessage(4, 1.5, FColor::Red, TEXT("Selecting canceled"));
	}
	UnitsInCursor.Empty();
}

void ARTSHUD::DrawRectangle_Implementation()
{
	CurrentPoint = GetMousePosition();
	DrawRect(FLinearColor(0, 0, 0.1, 0.15), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
	FoundUnitsInRect(InitialPoint, CurrentPoint);
}

void ARTSHUD::DebugMessage_Implementation()
{
	FString UnitsInCursorNum = UKismetStringLibrary::Conv_IntToString(UnitsInCursor.Num());
	FString UnitsInCursorNumMessage = FString::Printf(TEXT("Units by cursor found: ")) + UnitsInCursorNum;
	GEngine->AddOnScreenDebugMessage(3, 1.5, FColor::Yellow, UnitsInCursorNumMessage);
	
	FString UnitsInRectNum = UKismetStringLibrary::Conv_IntToString(UnitsInRect.Num());
	FString UnitsInRectNumMessage = FString::Printf(TEXT("Units in selection rectangle found: ")) + UnitsInRectNum;
	GEngine->AddOnScreenDebugMessage(2, 1.5, FColor::Yellow, UnitsInRectNumMessage);
	
	FString UnitsNum = UKismetStringLibrary::Conv_IntToString(SelectedUnits.Num());
	FString UnitsNumMessage = FString::Printf(TEXT("Units is selected: ")) + UnitsNum;
	GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Yellow, UnitsNumMessage);
}
