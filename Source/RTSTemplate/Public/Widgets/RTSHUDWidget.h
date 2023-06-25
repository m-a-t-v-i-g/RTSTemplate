// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "RTSTypes.h"
#include "Blueprint/UserWidget.h"
#include "RTSHUDWidget.generated.h"

class UCanvasPanel;
class UTextBlock;
class UImage;

UCLASS()
class RTSTEMPLATE_API URTSHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> HUDWidget_MainPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> HUDWidget_PlayerID;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> HUDWidget_PlayerColor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> HUDWidget_ImageColor;

public:
	FText GetPlayerIDText();
	
	FLinearColor GetPlayerColor();
	
};
