// Fill out your copyright notice in the Description page of Project Settings.


#include "HammerWeapon.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "MystCore/BuildingSystem/Structures/StructureBase.h"


// Sets default values
AHammerWeapon::AHammerWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHammerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHammerWeapon::Fire()
{
	if(CurrentStructure) CurrentStructure->PlaceStructure();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentStructure = GetWorld()->SpawnActor<AStructureBase>(StructureClass, SpawnParams);
	Super::Fire();
}


void AHammerWeapon::SetActiveWeapon(bool Val)
{
	Super::SetActiveWeapon(Val);

	if(Val)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		CurrentStructure = GetWorld()->SpawnActor<AStructureBase>(StructureClass, SpawnParams);
		CurrentStructure->SetActorLocation(BuildPreviewLocation());
		
	}else if(CurrentStructure)
	{
		CurrentStructure->Destroy();
	}
}

FVector AHammerWeapon::BuildPreviewLocation()
{
	FHitResult OutHit;
	Raycast(OutHit);
	return OutHit.Location;
}


void AHammerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!bIsActive) return;

	if(CurrentStructure) CurrentStructure->SetActorLocation(BuildPreviewLocation());
}

bool AHammerWeapon::Raycast(FHitResult& OutHit)
{
	FVector Start = CharacterOwner->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector CameraDirection = CharacterOwner->GetFirstPersonCameraComponent()->GetForwardVector();
	FVector End = Start + CameraDirection * RayTracingDistance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(CurrentStructure);
	CollisionQueryParams.AddIgnoredActor(CharacterOwner);
	
	bool b = GetWorld()->LineTraceSingleByProfile(OutHit, Start, End, FName("Visibility"), CollisionQueryParams);

	FHitResult OutHitToGround;
	bool bG = false;
	//Raycast to the Ground
	if(b)
	{
		FVector StartG = OutHit.Location;
		StartG.Z += 500;

		FVector EndG = OutHit.Location;
		EndG.Z -= 50;
		
		bG = GetWorld()->LineTraceSingleByProfile(OutHitToGround, StartG, EndG, FName("Visibility"), CollisionQueryParams);
	}else
	{
		FVector StartG = OutHit.TraceEnd;

		FVector EndG = OutHit.TraceEnd;
		EndG.Z -= RayTracingDistance;
		
		bG = GetWorld()->LineTraceSingleByProfile(OutHitToGround, StartG, EndG, FName("Visibility"), CollisionQueryParams);
	}

	OutHit = OutHitToGround;
	//DrawDebugCircle(GetWorld(), OutHit.Location, 20.0f, 50.0f, FColor::White, true, 10.0f);
	
	return bG;
}


