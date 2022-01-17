// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MeleeAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYSTCORE_API AMeleeAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeAIController();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI);
	UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI);
	UAIPerceptionComponent* PerceptionComponentMelee;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI);
	UAISenseConfig_Sight* SightConfig;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
