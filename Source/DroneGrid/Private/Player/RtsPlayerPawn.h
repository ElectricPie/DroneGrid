// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RtsPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS(Abstract)
class ARtsPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARtsPlayerPawn();

	UPROPERTY(VisibleAnywhere)
	bool bCanMove = false;

	UFUNCTION()
	void Move(FVector Direction);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 1800.f;
	UPROPERTY(EditAnywhere, Category="Movement", meta=(ToolTip="The distance +- from 0, 0 the pawn can move"))
	FVector2D Boundaries = FVector2D(2000.f, 2000.f);

	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};
