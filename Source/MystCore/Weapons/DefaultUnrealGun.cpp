// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultUnrealGun.h"

#include "MystCore/MystCoreProjectile.h"


// Sets default values
ADefaultUnrealGun::ADefaultUnrealGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADefaultUnrealGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultUnrealGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultUnrealGun::Fire()
{
	Super::Fire();
	UE_LOG(LogTemp, Warning, TEXT("bRUH"));
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector SpawnLocation = SkeletalMesh->GetSocketLocation(FName("Muzzle"));
	FRotator SpawnRotation = SkeletalMesh->GetSocketRotation(FName("Muzzle"));
	
	GetWorld()->SpawnActor<AMystCoreProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}


