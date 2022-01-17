// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMeleeEnemyCharacter::AMeleeEnemyCharacter() : Super()
{
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// brij
	
	AIControllerClass = AMeleeAIController::StaticClass();

}

// Called when the game starts or when spawned
void AMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMeleeEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMeleeEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

