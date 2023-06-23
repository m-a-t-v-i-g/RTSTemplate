// Real Time Strategy C++ template by matvig.

#include "Game/RTSCameraPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Game/RTSHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/RTSUnitInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

ARTSCameraPawn::ARTSCameraPawn()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(SceneComponent);
	SpringArmComponent->TargetArmLength = ZoomDegree * ZoomStep;
	SpringArmComponent->SetRelativeRotation(FRotator(-65.0, 0.0, 0.0));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 7.5;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 7.5;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FX_Cursor(TEXT("/Game/Cursor/FX_Cursor"));
	if (FX_Cursor.Object != nullptr)
	{
		FXCursor = FX_Cursor.Object;
	}
	
	PrimaryActorTick.bCanEverTick = true;
}

void ARTSCameraPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARTSCameraPawn, SelectedUnits);
}

void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;

	CameraPosition();
	UpdateZoom();
}

void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Started, this, &ARTSCameraPawn::CameraZoom);
		EnhancedInputComponent->BindAction(CameraRotationAction, ETriggerEvent::Triggered, this, &ARTSCameraPawn::CameraRotation);
		
		EnhancedInputComponent->BindAction(LeftMouseButtonAction, ETriggerEvent::Started, this, &ARTSCameraPawn::LeftMousePressed);
		EnhancedInputComponent->BindAction(LeftMouseButtonAction, ETriggerEvent::Completed, this, &ARTSCameraPawn::LeftMouseReleased);

		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Started, this, &ARTSCameraPawn::RightMousePressed);
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Completed, this, &ARTSCameraPawn::RightMouseReleased);

		EnhancedInputComponent->BindAction(LookAtDestinationAction, ETriggerEvent::Completed, this, &ARTSCameraPawn::LookAtDestinationPressed);
	}
}

void ARTSCameraPawn::CameraPosition()
{
	if (!GetWorld()) return;
	
	if (!GetPlayerController()) return;

	float MousePosX;
	float MousePosY;
	
	auto GetViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	auto GetMousePosition = GetPlayerController()->GetMousePosition(MousePosX, MousePosY);
	
	if (GetMousePosition)
	{
		const FRotator CameraRotation = CameraComponent->GetComponentRotation();
		const FRotator CameraRotationYaw(0.0, CameraRotation.Yaw, 0.0);

		FRotationMatrix Direction = FRotationMatrix(CameraRotationYaw);
		
		if (MousePosX / GetViewportSize.X >= 0.99)
		{
			AddActorLocalOffset(Direction.GetUnitAxis(EAxis::Y) * DeltaSeconds * CameraMovementSpeed);
		}
		else if (MousePosX / GetViewportSize.X <= 0.01)
		{
			AddActorLocalOffset(Direction.GetUnitAxis(EAxis::Y) * DeltaSeconds * CameraMovementSpeed * -1);
		}
		if (MousePosY / GetViewportSize.Y >= 0.99)
		{
			AddActorLocalOffset(Direction.GetUnitAxis(EAxis::X) * DeltaSeconds * CameraMovementSpeed * -1);
		}
		else if (MousePosY / GetViewportSize.Y <= 0.01)
		{
			AddActorLocalOffset(Direction.GetUnitAxis(EAxis::X) * DeltaSeconds * CameraMovementSpeed);
		}
	}
}

void ARTSCameraPawn::CameraZoom(const FInputActionValue& Value)
{
	if (!SpringArmComponent || !CameraComponent) return;
	
	if (Value.Get<float>() == 1.0)
	{
		ZoomDegree--;
		ZoomDegree = FMath::Clamp(ZoomDegree, ZoomMin, ZoomMax);
	}
	if (Value.Get<float>() == -1.0)
	{
		ZoomDegree++;
		ZoomDegree = FMath::Clamp(ZoomDegree, ZoomMin, ZoomMax);
	}
}

void ARTSCameraPawn::CameraRotation(const FInputActionValue& Value)
{
	if (!SpringArmComponent || !CameraComponent) return;

	FVector2D MouseDelta;
	GetPlayerController()->GetInputMouseDelta(MouseDelta.X, MouseDelta.Y);

	float RotationPitch = SpringArmComponent->GetComponentRotation().Pitch + MouseDelta.Y * CameraRotationSpeed;
	float RotationYaw = SpringArmComponent->GetComponentRotation().Yaw + MouseDelta.X * CameraRotationSpeed;

	SpringArmComponent->SetWorldRotation(FRotator(UKismetMathLibrary::Clamp(RotationPitch, -80.0, 0.0), RotationYaw, 0.0));
}

void ARTSCameraPawn::LeftMousePressed()
{
	if (!HUD) return;
	
	HUD->StartSelecting();
}

void ARTSCameraPawn::LeftMouseReleased()
{
	if (!HUD) return;

	HUD->StopSelecting();
}

void ARTSCameraPawn::RightMousePressed()
{

}

void ARTSCameraPawn::RightMouseReleased()
{
	if (HasUserTasks())
	{
		DeactivateOtherTasks();
		return;
	}
	
	if (HasSelectedUnits() && !HasUserTasks())
	{
		MoveUnitsToLocation();
		return;
	}
}

void ARTSCameraPawn::LookAtDestinationPressed()
{
	if (!HasSelectedUnits()) return;
	
	if (!bLookAtDestinationActive)
	{
		bLookAtDestinationActive = true;
		GEngine->AddOnScreenDebugMessage(2, 1.5, FColor::Cyan, TEXT("Task LookAtDestination is actived"));
	}
	else
	{
		bLookAtDestinationActive = false;
		GEngine->AddOnScreenDebugMessage(2, 1.5, FColor::Cyan, TEXT("Task LookAtDestination is deactived"));
	}
}

void ARTSCameraPawn::UpdateZoom()
{
	if (!SpringArmComponent) return;
	
	float CurrentZoom = SpringArmComponent->TargetArmLength;
	SpringArmComponent->TargetArmLength = UKismetMathLibrary::FInterpTo(CurrentZoom, ZoomDegree * ZoomStep, DeltaSeconds, 4.5);
}

void ARTSCameraPawn::GetSelectedUnits(const TArray<AActor*> &NewSelectedUnits)
{
	if (!HUD) return;

	SelectedUnits = NewSelectedUnits;
	ServerGetSelectedUnits(NewSelectedUnits);
}

bool ARTSCameraPawn::HasSelectedUnits()
{
	return SelectedUnits.Num() > 0;
}

void ARTSCameraPawn::MoveUnitsToLocation()
{
	if (!GetPlayerController()) return;
	
	FHitResult HitResult;
	
	GetPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	ServerCreateDestination(HitResult.Location);
	ClientCreateDestination(HitResult.Location);
}

void ARTSCameraPawn::UnitTaskCase(EUnitAssignTask NewTask)
{
	AssignTask = NewTask;
	switch (AssignTask)
	{
	case EUnitAssignTask::Idle:
		GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Cyan, TEXT("Task: Idle"));
		break;
	case EUnitAssignTask::MoveToDestination:
		GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Cyan, TEXT("Task: Move to destination"));
		break;
	case EUnitAssignTask::LookAtDestination:
		GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::Cyan, TEXT("Task: Look at destination"));
		break;
	default:
		break;
	}
}

bool ARTSCameraPawn::HasUserTasks()
{
	if (bLookAtDestinationActive)
	{
		return true;
	}
	return false;
}

void ARTSCameraPawn::DeactivateOtherTasks()
{
	bLookAtDestinationActive = false;

	GEngine->AddOnScreenDebugMessage(2, 1.5, FColor::Cyan, TEXT("All tasks is deactivated"));
}

void ARTSCameraPawn::InitInputs_Implementation()
{
	if (!GetPlayerController()) return;

	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer());
	if (!Subsystem) return;
	
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ARTSCameraPawn::InitHUD_Implementation()
{
	if (!GetPlayerController()) return;

	auto GetHUD = GetPlayerController()->GetHUD();
	if (!GetHUD) return;

	HUD = Cast<ARTSHUD>(GetHUD);
	HUD->OnUpdateSelectedUnits.AddUObject(this, &ARTSCameraPawn::GetSelectedUnits);
}

void ARTSCameraPawn::ServerGetSelectedUnits_Implementation(const TArray<AActor*> &NewSelectedUnits)
{
	SelectedUnits = NewSelectedUnits;
}

void ARTSCameraPawn::ServerCreateDestination_Implementation(FVector HitLocation)
{
	for (auto SelectedUnit : SelectedUnits)
	{
		auto TempUnit = Cast<IRTSUnitInterface>(SelectedUnit);
		if (TempUnit)
		{
			TempUnit->CachedDestination = HitLocation;
			TempUnit->RefreshTask(EUnitCurrentTask::MoveToDestination);
		}
	}
}

void ARTSCameraPawn::ClientCreateDestination_Implementation(FVector HitLocation)
{
	if (!GetWorld()) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator,
	                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}
