// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);

UCLASS(BlueprintType)
class MYSTCORE_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float Damage = 20.0f;

	//Delegate OnFire
	UPROPERTY(BlueprintAssignable)
	FOnFire OnFire;
	
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	bool bIsActive;
	
	/* Gun Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	USkeletalMeshComponent* SkeletalMesh;

	/* Weapon Owner */
	UPROPERTY(BlueprintReadWrite, Category=Appearence)
	AController* Shooter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetActiveWeapon(bool Val);

	virtual void Fire();
	
	virtual void SetShooter(AController* ShooterController);
};
