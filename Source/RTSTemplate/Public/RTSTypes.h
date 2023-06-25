// Real Time Strategy C++ template by matvig.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RTSTypes.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FGameData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "16"))
	int PlayersNum = 1;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct FUnit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "16"))
	int PlayerID = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "16"))
	int TeamID = 1;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct FHuman
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EUserTaskForUnit : uint8
{
	Empty UMETA(DisplayName = "Empty"),
	
	LookAt UMETA(DisplayName = "Look At"),
};

UCLASS()
class RTSTEMPLATE_API URTSTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
