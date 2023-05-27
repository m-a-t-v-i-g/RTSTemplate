// Real Time Strategy C++ template by matvig.

#include "Game/RTSHUD.h"
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
	if (SelectedUnits.Num() > 0)
	{
		for (auto SelectedUnit : SelectedUnits)
		{
			for (auto UnitInCursor : UnitsInCursor)
			{
				if (SelectedUnit == UnitInCursor || UnitsInCursor.Contains(SelectedUnit)) return;
			}
		}
	}
	
	bSelecting = true;
	InitialPoint = GetMousePosition();

	ClearSelectedUnits();
}

void ARTSHUD::StopSelecting()
{
	bSelecting = false;

	UpdateSelectedUnits();
	DebugUnits();
}

void ARTSHUD::FoundUnitByCursor()
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
			UnitsInCursor.AddUnique(UnitInterface);
		}
		if (!UnitInterface && UnitsInCursor.Num() > 0)
		{
			for (int i = 0; i < UnitsInCursor.Num(); i++)
			{
				UnitsInCursor[i]->SetUnitIsFound(false);
				UnitsInCursor.RemoveAt(i);
			}
		}
	}
}

void ARTSHUD::FoundUnitsInRect(FVector2D FirstPoint, FVector2D SecondPoint)
{
	TArray<AActor*> FoundUnits;
	auto GetUnitsInRect = GetUnitsInSelectionRectangle<AActor>(FirstPoint, SecondPoint, FoundUnits, false, false);
	if (GetUnitsInRect)
	{
		for (auto FoundUnit : FoundUnits)
		{
			auto TempUnit = Cast<IRTSUnitInterface>(FoundUnit);
			if (TempUnit)
			{
				if (!UnitsInRect.Contains(TempUnit))
				{
					TempUnit->SetUnitIsFound(true);
					UnitsInRect.AddUnique(TempUnit);
				}
			}
		}
		for (int i = 0; i < UnitsInRect.Num(); i++)
		{
			auto TempUnit = UnitsInRect[i];
			if (TempUnit)
			{
				if (!FoundUnits.Contains(Cast<AActor>(TempUnit)))
				{
					TempUnit->SetUnitIsFound(false);
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
		TArray<AActor*> TempUnits;
		for (auto UnitInRect : UnitsInRect)
		{
			auto TempUnit = Cast<AActor>(UnitInRect);
			if (IsValid(TempUnit))
			{
				UnitInRect->SetUnitIsFound(false);
				UnitInRect->SetUnitIsSelected(true);
				TempUnits.AddUnique(TempUnit);
			}
		}
		SelectedUnits = UnitsInRect;
		UnitsInRect.Empty();

		OnUpdateSelectedUnits.Broadcast(TempUnits);
	}
}

void ARTSHUD::ClearSelectedUnits()
{
	if (SelectedUnits.Num() > 0)
	{
		TArray<AActor*> TempUnits;
		for (auto SelectedUnit : SelectedUnits)
		{
			if (UnitsInCursor.Contains(SelectedUnit))
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
				TempUnits.Empty();
			}
		}
		SelectedUnits.Empty();
		
		OnUpdateSelectedUnits.Broadcast(TempUnits);
	}
	UnitsInCursor.Empty();
}

void ARTSHUD::DebugUnits()
{
	if (SelectedUnits.Num() <= 0) return;
	
	for (auto SelectedUnit : SelectedUnits)
	{
		auto SelectedActor = Cast<AActor>(SelectedUnit);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SelectedActor->GetName());
	}
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
	FString UnitsNumMessage = FString::Printf(TEXT("Units is selected by HUD: ")) + UnitsNum;
	GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Yellow, UnitsNumMessage);
}
