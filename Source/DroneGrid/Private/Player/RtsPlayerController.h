// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RtsPlayerController.generated.h"

class ARtsPlayerPawn;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS(Abstract)
class ARtsPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* UnlockCameraAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveCameraAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ZoomCameraAction;

	UPROPERTY(VisibleAnywhere)
	ARtsPlayerPawn* PlayerPawn;

	bool bMouseIsLocked = false;

	FVector2D LockedMousePosition;

	TWeakObjectPtr<UGameViewportClient> ViewportClient;

	UFUNCTION()
	void UnlockCamera();
	UFUNCTION()
	void LockCamera();
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Zoom(const FInputActionValue& Value);
};
