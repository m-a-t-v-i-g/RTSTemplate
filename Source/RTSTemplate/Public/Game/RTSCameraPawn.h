// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ARTSHUD;

UCLASS()
class RTSTEMPLATE_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ARTSCameraPawn();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftMouseButtonAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RightMouseButtonAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraRotationAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "HUD")
	TObjectPtr<ARTSHUD> HUD;

	TArray<ARTSUnit*> SelectedUnits;

	float DeltaSeconds = 0.0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraMovementSpeed = 3000.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraRotationSpeed = 2.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	int ZoomMin = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	int ZoomDegree = 6;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	int ZoomMax = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	float ZoomStep = 200.0;

	bool bRotatingCamera = false;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CameraPosition();
	void CameraZoom(const FInputActionValue& Value);
	void CameraRotation(const FInputActionValue& Value);

	void LeftMousePressed();
	void LeftMouseReleased();
	
	void RightMousePressed();
	void RightMouseReleased();
	
	void UpdateZoom();

	void GetSelectedUnits();
	bool HasSelectedUnits();
	
	void MoveUnitsToLocation();
	
protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Pawn")
	APlayerController* GetPlayerController()
	{
		return Cast<APlayerController>(GetController());
	}

public:
	UFUNCTION(Client, Reliable)
	void InitInputs();
	
	UFUNCTION(Client, Reliable)
	void InitHUD();
	
	UFUNCTION(Server, Reliable)
	void ServerGetSelectedUnits(const TArray<ARTSUnit*> &GetSelectedUnits);
	
	UFUNCTION(Server, Reliable)
	void ServerMoveUnitsToLocation(FHitResult GetHitResult);
	
	UFUNCTION(Client, Reliable)
	void ClientMoveLocationPoint(FVector HitLocation);
};
