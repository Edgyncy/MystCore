// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnManaUpdate);

UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTCORE_API UManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManaComponent();

	UPROPERTY(BlueprintAssignable)
	FOnManaUpdate OnManaUpdate;

	// Maximum mana of Actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mana");
	float DefaultMana;

	// Current mana of Actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mana")
	float Mana;

	// Regeneration speed of Mana
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mana");
	float RegenerationSpeed = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Timer that regenerates mana
	FTimerHandle RegenerationTimer;

	UFUNCTION()
	void RegenerationTimerFunction();

public:
	
	
	UFUNCTION(BlueprintCallable)
	void SuckMana(float Amount);

	UFUNCTION(BlueprintCallable)
	void RegenerateMana(float Amount);

	
};
