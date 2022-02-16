// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Actor.h"
#include "MystCore/MystCoreCharacter.h"
#include "RayTracingWeapon.generated.h"

UCLASS()
class MYSTCORE_API ARayTracingWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARayTracingWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Raytrace);
	int RayTracingDistance = 10000.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AMystCoreCharacter* CharacterOwner;
	
	virtual bool Raycast(FHitResult& OutHit);

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetShooter(AController* ShooterController) override;

	/* Yes, Animation Feature is in RayTracingWeapon.cpp. So What? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	UAnimMontage* FireAnimation;
	
	virtual void Fire() override;
};
