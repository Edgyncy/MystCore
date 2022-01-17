// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZeroHealth);

UCLASS(BlueprintType)
class MYSTCORE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnZeroHealth OnZeroHealth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
    void LandedThing(const FHitResult& Hit);
	
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

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
