// Fill out your copyright notice in the Description page of Project Settings.


#include "FireballAbility.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MystCore/Utils/ExplosionImpulse.h"

AFireballAbility::AFireballAbility()
{
	
}

void AFireballAbility::BeginPlay()
{
	Super::BeginPlay();
}

void AFireballAbility::ProjectileFinish(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	Super::ProjectileFinish(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	TArray<AActor*> IgnoreActors;
	//IgnoreActors.Add(Character);

	UE_LOG(LogTemp, Warning, TEXT("Radial Damge"))

	FExplosionImpulseInfo Info;
	Info.Radius = ExplosionRadius;
	Info.Strength = ExplosionImpulseStrength;

	FVector ExplosionLocation = Hit.Location;
	ExplosionLocation.Z += 30.0f;
	
	AExplosionImpulse::CreateAndExplode(GetWorld(), ExplosionLocation, Info);
	
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage,
		Hit.Location, ExplosionRadius, nullptr,
		IgnoreActors, this, Caster->GetInstigatorController(), false, ECC_Visibility);
}


void AFireballAbility::Cast(ACharacter* CasterActor)
{
	Super::Cast(CasterActor);

	FinishCasting();
}



