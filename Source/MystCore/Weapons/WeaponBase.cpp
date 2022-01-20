// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh Component");
	SkeletalMesh->SetupAttachment(RootComponent);

	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::SetActiveWeapon(bool Val)
{
	bIsActive = Val;
	SetActorHiddenInGame(!Val);
}

void AWeaponBase::Fire()
{
	OnFire.Broadcast();
}



// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

