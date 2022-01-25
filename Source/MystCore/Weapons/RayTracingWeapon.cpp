// Fill out your copyright notice in the Description page of Project Settings.


#include "RayTracingWeapon.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "MystCore/MystCoreCharacter.h"


// Sets default values
ARayTracingWeapon::ARayTracingWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARayTracingWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARayTracingWeapon::SetShooter(AController* ShooterController)
{
	Super::SetShooter(ShooterController);
	
	AMystCoreCharacter* Character = (AMystCoreCharacter*) Shooter->GetCharacter();
	if(!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is not parented to an object"))
	}
	
	CharacterOwner = Character;
}


bool ARayTracingWeapon::Raycast(FHitResult& OutHit)
{
	FVector StartMuzzle = SkeletalMesh->GetSocketLocation(FName("Muzzle"));

	FVector Start = CharacterOwner->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector CameraDirection = CharacterOwner->GetFirstPersonCameraComponent()->GetForwardVector();
	FVector End = Start + CameraDirection * RayTracingDistance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(CharacterOwner);
	
	bool b = GetWorld()->LineTraceSingleByProfile(OutHit, Start, End, FName("Projectile"), CollisionQueryParams);
	//DrawDebugCircle(GetWorld(), OutHit.Location, 20.0f, 50.0f, FColor::White, true, 10.0f);

	return b;
}


// Called every frame
void ARayTracingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

