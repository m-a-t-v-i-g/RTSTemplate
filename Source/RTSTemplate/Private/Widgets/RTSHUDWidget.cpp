// Real Time Strategy C++ template by matvig.

#include "Widgets/RTSHUDWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game/RTSPlayerState.h"

void URTSHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void URTSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HUDWidget_PlayerID)
	{
		HUDWidget_PlayerID->SetText(GetPlayerIDText());
	}
	if (HUDWidget_PlayerColor)
	{
		HUDWidget_PlayerColor->SetText(FText::FromString(FString::Printf(TEXT("Your color: "))));
	}
	if (HUDWidget_ImageColor)
	{
		HUDWidget_ImageColor->SetColorAndOpacity(GetPlayerColor());
	}
}

FText URTSHUDWidget::GetPlayerIDText()
{
	auto PlayerState = Cast<ARTSPlayerState>(GetOwningPlayer()->PlayerState);
	if (!PlayerState) return FText::FromString(FString::Printf(TEXT("Player ID: Invalid")));

	return FText::FromString(FString::Printf(TEXT("Player ID: %i"), PlayerState->GetPlayerID()));
}

FLinearColor URTSHUDWidget::GetPlayerColor()
{
	auto PlayerState = Cast<ARTSPlayerState>(GetOwningPlayer()->PlayerState);
	if (!PlayerState) return FLinearColor::Red;

	switch (PlayerState->GetPlayerID())
	{
	case 1:
		return FLinearColor::White;
	case 2:
		return FLinearColor::Red;
	case 3:
		return FLinearColor::Green;
	case 4:
		return FLinearColor::Yellow;
	case 5:
		return FLinearColor::Blue;
	default:
		return FLinearColor::Gray;
	}
}
