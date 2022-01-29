﻿// Fill out your copyright notice in the Description page of Project Settings.


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
	//if(CharacterOwner->ManaComponent->Mana <= 100) return;
	//CharacterOwner->ManaComponent->SuckMana(100);
	
	Super::Fire();
}

