// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MeleeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "MeleeEnemyCharacter.generated.h"

UCLASS()
class MYSTCORE_API AMeleeEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
