// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RtsPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RtsPlayerPawn.h"

void ARtsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	bShowMouseCursor = true;

	PlayerPawn = Cast<ARtsPlayerPawn>(GetPawn());

	if (GEngine && GEngine->GameViewport)
	{
		ViewportClient = GEngine->GameViewport;
	}

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
	}
}

void ARtsPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Keeps the mouse cursor in the centre of the screen as it will prevent movement when the cursor hits the edge of the screen
	if (bMouseIsLocked)
	{
		FVector2d ViewportSize;
		ViewportClient->GetViewportSize(ViewportSize);
		SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
	}
}

void ARtsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(UnlockCameraAction, ETriggerEvent::Started, this,
		                                   &ARtsPlayerController::UnlockCamera);
		EnhancedInputComponent->BindAction(UnlockCameraAction, ETriggerEvent::Completed, this,
		                                   &ARtsPlayerController::LockCamera);
		EnhancedInputComponent->BindAction(UnlockCameraAction, ETriggerEvent::Canceled, this,
		                                   &ARtsPlayerController::LockCamera);

		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this,
		                                   &ARtsPlayerController::Move);
	}
}

void ARtsPlayerController::UnlockCamera()
{
	if (PlayerPawn == nullptr) return;

	PlayerPawn->bCanMove = true;
	bShowMouseCursor = false;
	bMouseIsLocked = true;

	GetMousePosition(LockedMousePosition.X, LockedMousePosition.Y);
}

void ARtsPlayerController::LockCamera()
{
	if (PlayerPawn == nullptr) return;

	PlayerPawn->bCanMove = false;
	bShowMouseCursor = true;
	bMouseIsLocked = false;

	SetMouseLocation(LockedMousePosition.X, LockedMousePosition.Y);
}

void ARtsPlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerPawn == nullptr) return;

	const FVector MoveAxisValue = Value.Get<FVector>();
	PlayerPawn->Move(MoveAxisValue.GetSafeNormal());
}
