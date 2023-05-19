// Real Time Strategy C++ template by matvig.

#include "Game/RTSCameraPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARTSCameraPawn::ARTSCameraPawn()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(SceneComponent);
	SpringArmComponent->TargetArmLength = 1800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-65.0f, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 7.5f;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 7.5;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	PrimaryActorTick.bCanEverTick = true;
}

void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;

	MovePosition();
}

void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//EnhancedInputComponent->BindAction(LeftMouseButtonAction, ETriggerEvent::Completed, this, &ARTSCameraPawn::LeftMouseClick);
		//EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Completed, this, &ARTSCameraPawn::RightMouseClick);
	}
}


void ARTSCameraPawn::MovePosition()
{
	if (!GetWorld()) return;
	
	if (!GetPlayerController()) return;

	float MousePosX;
	float MousePosY;
	auto GetViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	auto GetMousePosition = GetPlayerController()->GetMousePosition(MousePosX, MousePosY);

	if (GetMousePosition)
	{
		if (MousePosX / GetViewportSize.X >= 0.99)
		{
			AddActorLocalOffset(FVector(0.0, DeltaSeconds * CameraSpeed, 0.0));
		}
		else if (MousePosX / GetViewportSize.X <= 0.01)
		{
			AddActorLocalOffset(FVector(0.0, DeltaSeconds * CameraSpeed * -1, 0.0));
		}
		if (MousePosY / GetViewportSize.Y >= 0.99)
		{
			AddActorLocalOffset(FVector(DeltaSeconds * CameraSpeed * -1, 0.0, 0.0));
		}
		else if (MousePosY / GetViewportSize.Y <= 0.01)
		{
			AddActorLocalOffset(FVector(DeltaSeconds * CameraSpeed, 0.0, 0.0));
		}
	}
}
