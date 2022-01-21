// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AProjectileWeapon::AProjectileWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileWeapon::Fire()
{
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector SpawnLocation = SkeletalMesh->GetSocketLocation(FName("Muzzle"));
	//FRotator SpawnRotation = SkeletalMesh->GetSocketRotation(FName("Muzzle"));

	FHitResult Hit;
	bool bHit = Raycast(Hit);
	
	FVector End = Hit.Location;
	if(!bHit) End = Hit.TraceEnd;
	
	FVector Start = SpawnLocation;

	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
	
	AMystCoreProjectile* ProjectileActor = GetWorld()->SpawnActor<AMystCoreProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	ProjectileActor->OnActorHit.AddDynamic(this, &AProjectileWeapon::OnProjectileHit);
}

void AProjectileWeapon::OnProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Shooter, SelfActor, NULL);
}


// Called every frame
void AProjectileWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

