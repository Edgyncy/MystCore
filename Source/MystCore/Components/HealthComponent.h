// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZeroHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdate);

UCLASS(BlueprintType)
class MYSTCORE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnZeroHealth OnZeroHealth;
	
	UPROPERTY(BlueprintAssignable)
	FOnZeroHealth OnHealthUpdate;

	// Regeneration delay after character was damaged
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Regeration);
	float HealthRegenerationDelay = 10.f;

	// Is Character currently regenerating health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Regeration);
	bool bIsRegenerating = false;

	// Regeneration speed of health (Health/Sec)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Regeneration);
	float RegenerationSpeed = 1;

	/** Adding Health **/
	UFUNCTION()
	void AddHealth(float Amount);

	/** Removing Health **/
	UFUNCTION()
	void RemoveHealth(float Amount);

protected:

	// Timer that regenerates health
	FTimerHandle RegenerationTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Regeneration);
	bool bCanRegenerate = false;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
    void LandedThing(const FHitResult& Hit);
	
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/** Sets bCanRegenerate bool which specifies ability of the character to regenerate health **/
	UFUNCTION()
	void SetCanRegenerate(bool CanRegenerate);

	/** Reloads Regeneration Timer (If bCanRegenerate has been changed)**/
	UFUNCTION()
	void ReloadRegeneration();

	/** Adding Health on constant Rate**/
	UFUNCTION()
    void RegenerationTimerFunction();

	/** Stop regeneration timer **/
	UFUNCTION()
    void RegenerationStop();

	/** Restart regeneration with delay (Example: Character was damaged) **/
	UFUNCTION()
	void RegenerationRestart(float &Delay);

public:
	
	//Health things
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health");
	float DefaultHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	float Health;

	//Fall Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FallDamage")
	float FallDamageStart = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FallDamage")
	bool FallDamageEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FallDamage")
	float FallDamageMultiplier = 0.04;
		
};
