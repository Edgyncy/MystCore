// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RayTracingWeapon.h"
#include "WeaponBase.h"
#include "GameFramework/Actor.h"
#include "MystCore/BuildingSystem/Structures/StructureBase.h"
#include "HammerWeapon.generated.h"

UCLASS()
class MYSTCORE_API AHammerWeapon : public ARayTracingWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHammerWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AStructureBase* CurrentStructure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AStructureBase> StructureClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetActiveWeapon(bool Val) override;

	virtual bool Raycast(FHitResult& OutHit) override;

	virtual FVector BuildPreviewLocation();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;
};
