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

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* UnlockCameraAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveCameraAction;

	UPROPERTY(VisibleAnywhere)
	ARtsPlayerPawn* PlayerPawn;

	UFUNCTION()
	void UnlockCamera();
	UFUNCTION()
	void LockCamera();
	UFUNCTION()
	void Move(const FInputActionValue& Value);
};
