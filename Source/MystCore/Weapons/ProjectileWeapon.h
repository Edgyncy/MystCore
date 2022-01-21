// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RayTracingWeapon.h"
#include "MystCore/MystCoreProjectile.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class MYSTCORE_API AProjectileWeapon : public ARayTracingWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMystCoreProjectile> ProjectileClass = AMystCoreProjectile::StaticClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;
};
