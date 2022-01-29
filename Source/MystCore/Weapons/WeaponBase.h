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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float FireRate = 0.5f;

	float StartDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bAuto = false;

	//Delegate OnFire
	UPROPERTY(BlueprintAssignable)
	FOnFire OnFire;
	
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	USoundBase* FireSound;
	
	/* Gun Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	USkeletalMeshComponent* SkeletalMesh;

	/* Weapon Owner */
	UPROPERTY(BlueprintReadWrite, Category=Appearence)
	AController* Shooter;

	bool bIsShooting;

	bool bIsInShootingDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTimerHandle FireTimerHandle;

private:

	FTimerHandle FireDelayHandle;
	
	UFUNCTION()
	void DisableFireDelay();

	UFUNCTION()
	void SetupFireDelay(float Delay);
	
	UFUNCTION()
	void EnableFireDelay();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetActiveWeapon(bool Val);

	virtual void StartFire();

	virtual void StopFire();
	
	virtual void Fire();
	
	virtual void SetShooter(AController* ShooterController);
};
