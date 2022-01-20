// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Actor.h"
#include "MystCore/MystCoreProjectile.h"
#include "DefaultUnrealGun.generated.h"

UCLASS()
class MYSTCORE_API ADefaultUnrealGun : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADefaultUnrealGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMystCoreProjectile> ProjectileClass = AMystCoreProjectile::StaticClass() ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;
};
