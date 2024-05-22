// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RtsPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARtsPlayerPawn::ARtsPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	RootComponent = Root;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void ARtsPlayerPawn::Move(FVector Direction)
{
	if (!bCanMove) return;

	const FVector DeltaLocation = Direction * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	const FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + GetTransform().TransformVector(DeltaLocation);

	// Clamp the pawn with in the boundaries
	if (!FMath::IsWithin(NewLocation.X, -Boundaries.X, Boundaries.X))
	{
		NewLocation.X = CurrentLocation.X;	
	}
	if (!FMath::IsWithin(NewLocation.Y, -Boundaries.Y, Boundaries.Y))
	{
		NewLocation.Y = CurrentLocation.Y;
	}
	
	SetActorLocation(NewLocation);
}

// Called when the game starts or when spawned
void ARtsPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARtsPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARtsPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
