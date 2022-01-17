// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilityActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishCast);

USTRUCT(BlueprintType)
struct FAbilityInformation
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CastTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconImage;
};

UCLASS()
class MYSTCORE_API AAbilityActor : public AActor
{
	GENERATED_BODY()
	
public:

	/** Finish Casting Event **/
	FOnFinishCast OnFinishCast;
	
	// Sets default values for this actor's properties
	AAbilityActor();

	/** Ability Details like: Name, Description etc.**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Ability)
	FAbilityInformation AbilityDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Ability)
	USoundBase* AbilitySound;

	UFUNCTION()
	virtual void Cast();

	UFUNCTION()
    virtual void ExecuteAbilitySound();

	UFUNCTION()
	void FinishCasting();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
