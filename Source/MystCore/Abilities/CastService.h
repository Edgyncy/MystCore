// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityActor.h"
#include "MystCore/Components/ManaComponent.h"
#include "UObject/Object.h"
#include "CastService.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreCast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostCast, bool, Canceled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCooldownUpdate, float, EstimatedTime, float, CooldownTime);
/**
 * Caster Service provides you a proper use of Abilities
 * There you can use cooldowns, cast time and blblalblablabla
 */
UCLASS(BlueprintType)
class MYSTCORE_API UCastService : public UObject
{
	GENERATED_BODY()

public:

	// Cooldown Update Timer
	FTimerHandle UpdateTimer;

	/** When Cast Is Starting **/
	UPROPERTY(BlueprintAssignable)
	FOnPreCast OnPreCast;
	
	/** When Casting Is Over **/
	UPROPERTY(BlueprintAssignable)
	FOnPostCast OnPostCast;
	
	/** Cooldown Update Delegate for HUD purposes **/
	UPROPERTY(BlueprintAssignable)
	FOnCooldownUpdate OnCooldownUpdate;

	/** Cooldown Start Event **/
	UPROPERTY(BlueprintAssignable)
	FOnCooldownStart OnCooldownStart;

	/** Cooldown End Event **/
	UPROPERTY(BlueprintAssignable)
	FOnCooldownEnd OnCooldownEnd;
	
	UCastService();

	UFUNCTION()
	void Cast(UWorld* world, FVector Location, FRotator Rotation);
	
	UFUNCTION()
	void StartCooldown();
	
	UFUNCTION()
	void UpdateCooldown();

	UFUNCTION()
    void EndCooldown();

	/** Ability **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<AAbilityActor> AbilityClass;

	/** ManaComponent **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UManaComponent* ManaComponent;

	/** Is Cooldown over **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	bool IsAvailable = true;

	/** Time until Cooldown is over **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	float EstimatedTime;

	/** Time until Cooldown is over **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	float CooldownTime;

	/** Cooldown Update Rate 1 = 1 sec**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float CooldownUpdateRate = 0.01f;

private:
	AAbilityActor* AbilityActor;

	UWorld* CurrentWorld;
	
};
