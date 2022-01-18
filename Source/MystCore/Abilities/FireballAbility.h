// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileAbility.h"
#include "FireballAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYSTCORE_API AFireballAbility : public AProjectileAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Explosion);
	float ExplosionImpulseStrength = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Explosion);
	float ExplosionDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Explosion);
	float ExplosionRadius = 1000.f;

protected:
	AFireballAbility();
	
	virtual void Cast(ACharacter* CasterActor) override;

	virtual void BeginPlay() override;

	virtual void ProjectileFinish(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
