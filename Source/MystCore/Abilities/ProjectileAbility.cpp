// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileAbility.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MystCore/MystCoreCharacter.h"

AProjectileAbility::AProjectileAbility()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	
	FXComponent = CreateDefaultSubobject<UNiagaraComponent>("FX Instance Default");
	FXComponent->SetupAttachment(RootComponent);
	
	FXDestroy = CreateDefaultSubobject<UNiagaraComponent>("FX Instance Destroy");
	FXDestroy->SetupAttachment(RootComponent);
}

void AProjectileAbility::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileAbility::ProjectileHit);
}


void AProjectileAbility::ProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FXComponent->Deactivate();
	FXDestroy->Activate();
}


void AProjectileAbility::Cast()
{
	
}


