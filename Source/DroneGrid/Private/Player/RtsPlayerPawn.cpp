// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RtsPlayerPawn.h"

// Sets default values
ARtsPlayerPawn::ARtsPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

