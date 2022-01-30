// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RayTracingWeapon.h"
#include "GameFramework/Actor.h"
#include "HitscanWeapon.generated.h"

UCLASS()
class MYSTCORE_API AHitscanWeapon : public ARayTracingWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHitscanWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire() override;
	
};
