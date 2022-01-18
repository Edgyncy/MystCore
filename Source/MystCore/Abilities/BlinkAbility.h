// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MystCore/MystCoreCharacter.h"

#include "BlinkAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYSTCORE_API ABlinkAbility : public AAbilityActor
{
	GENERATED_BODY()

public:
	ABlinkAbility();
	
	virtual void Cast(ACharacter* CasterActor) override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void FOVAnimation();

	FTimerHandle FOVAnimationTimer;
	float FOVAnimationSpeed = .1f;
	float FOVAnimationScale = 10.f;

	UFUNCTION()
	void Delay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	UNiagaraComponent* DashLinesFXComponent;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FuckZ = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ResetVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BasedOnVelocity = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlinkDistance = 1000.f;

private:
	float FOVDefault;
	float FOVCurrent;
	float FOVAnimationAlpha = 0.f;
	AMystCoreCharacter* Character;
	
};
