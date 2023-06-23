// Real Time Strategy C++ template by matvig.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "RTSTypes.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UNiagaraSystem;
class ARTSHUD;

UCLASS()
class RTSTEMPLATE_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ARTSCameraPawn();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAtDestinationAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "HUD")
	TObjectPtr<ARTSHUD> HUD;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "HUD", Replicated)
	TArray<AActor*> SelectedUnits;

	float DeltaSeconds = 0.0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraMovementSpeed = 3000.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraRotationSpeed = 4.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	int ZoomMin = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	int ZoomDegree = 6;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	int ZoomMax = 16;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Zoom")
	float ZoomStep = 200.0;

	bool bRotatingCamera = false;

	EUserChooseTask ChooseTask = EUserChooseTask::Idle;
	EUnitAssignTask AssignTask = EUnitAssignTask::Idle;

private:
	bool bLookAtDestinationActive = false;
	
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

	void LookAtDestinationPressed();
	
	void UpdateZoom();

	void GetSelectedUnits(const TArray<AActor*>& NewSelectedUnits);
	bool HasSelectedUnits();
	
	void MoveUnitsToLocation();
	
	void UnitTaskCase(EUnitAssignTask NewTask);

	bool HasUserTasks();
	void DeactivateOtherTasks();
	
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
	void ServerGetSelectedUnits(const TArray<AActor*> &NewSelectedUnits);
	
	UFUNCTION(Server, Reliable)
	void ServerCreateDestination(FVector HitLocation);
	
	UFUNCTION(Client, Reliable)
	void ClientCreateDestination(FVector HitLocation);

};
