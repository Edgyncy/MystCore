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

protected:
	AFireballAbility();
	
	virtual void Cast() override;

	virtual void BeginPlay() override;
	
};
