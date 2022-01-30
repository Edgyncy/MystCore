// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanWeapon.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
	
}

// Called when the game starts or when spawned
void AHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHitscanWeapon::Fire()
{
	Super::Fire();

	FHitResult Hit;
	bool bHit = Raycast(Hit);

	if(!bHit) return;
	
	AActor* ActorToDamage = Hit.GetActor();

	if(ActorToDamage && ActorToDamage->CanBeDamaged())
	{
		UGameplayStatics::ApplyDamage(ActorToDamage, Damage, Shooter, Shooter, NULL);
	}
}


