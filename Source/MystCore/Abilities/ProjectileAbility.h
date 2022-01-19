// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityActor.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYSTCORE_API AProjectileAbility : public AAbilityActor
{
	GENERATED_BODY()


protected:

	

	virtual void BeginPlay() override;
	
	virtual void Cast(ACharacter* CasterActor) override;

	UFUNCTION()
    virtual void ExecuteHitSound();

	UFUNCTION()
    virtual void StopFlySound();

	UFUNCTION()
    virtual void ExecuteFlySound();

	UFUNCTION()
    virtual void ProjectileDestroy();

	UFUNCTION()
	virtual void ProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
    virtual void ProjectileFinish(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:

	/** Is Projectile Finished all things */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Movement)
	bool bDead = false;

	AProjectileAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	UProjectileMovementComponent* ProjectileMovement;

	/** Life after projectile finished all things (Important for Explosion FX) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	float LifeAfterFinish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sounds)
	UAudioComponent* HitSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sounds)
	UAudioComponent* FlySoundComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	bool FXEnabled;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	UNiagaraComponent* FXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	UNiagaraComponent* FXDestroy;
	
	
};
