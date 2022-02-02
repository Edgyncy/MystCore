// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MystCore/Components/HealthComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS(BlueprintType)
class MYSTCORE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Health);
	UHealthComponent* HealthComponent;

	UPROPERTY(BlueprintReadWrite);
	AActor* Target;
	
	UPROPERTY(BlueprintReadWrite);
	AController* LastDamageBy;

	UPROPERTY(BlueprintReadWrite);
	ACharacter* LastDamageCharacterBy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
    void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnDeath();

};
