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

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
	}
}

void ARtsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(UnlockCameraAction, ETriggerEvent::Started, this, &ARtsPlayerController::UnlockCamera);
		EnhancedInputComponent->BindAction(UnlockCameraAction, ETriggerEvent::Completed, this, &ARtsPlayerController::LockCamera);
		EnhancedInputComponent->BindAction(UnlockCameraAction, ETriggerEvent::Canceled, this, &ARtsPlayerController::LockCamera);
	}
}

void ARtsPlayerController::UnlockCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Unlocking Camera"));
	if (PlayerPawn == nullptr) return;

	PlayerPawn->bCanMove = true;
}

void ARtsPlayerController::LockCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Locking Camera"));
	if (PlayerPawn == nullptr) return;
	
	PlayerPawn->bCanMove = false;
}
