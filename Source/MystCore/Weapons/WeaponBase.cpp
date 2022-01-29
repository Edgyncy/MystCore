// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"


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

void AWeaponBase::SetShooter(AController* ShooterController)
{
	Shooter = ShooterController;
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

void AWeaponBase::StartFire()
{
	//SetupFireDelay(FireRate);
	if(bAuto)
	{
		if(bIsInShootingDelay)
		{
			float RemainingTime = GetWorldTimerManager().GetTimerRemaining(FireDelayHandle);
			UE_LOG(LogTemp, Warning, TEXT("Remaining Time: %f"), RemainingTime)
			bIsShooting = true;
			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AWeaponBase::Fire, FireRate, true, RemainingTime);
		}else
		{
			bIsShooting = true;
			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AWeaponBase::Fire, FireRate, true);
		}
	}

	if(bIsInShootingDelay) return;
	Fire();
}

void AWeaponBase::DisableFireDelay()
{
	bIsInShootingDelay = false;
}

void AWeaponBase::EnableFireDelay()
{
	bIsInShootingDelay = true;
}

void AWeaponBase::SetupFireDelay(float Delay)
{
	GetWorldTimerManager().ClearTimer(FireDelayHandle);
	EnableFireDelay();
	
	GetWorldTimerManager().SetTimer(FireDelayHandle, this, &AWeaponBase::DisableFireDelay, Delay, false);
}

void AWeaponBase::StopFire()
{
	bIsShooting = false;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void AWeaponBase::Fire()
{
	SetupFireDelay(FireRate);
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	OnFire.Broadcast();
}



// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

