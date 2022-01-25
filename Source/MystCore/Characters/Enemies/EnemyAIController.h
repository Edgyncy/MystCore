// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYSTCORE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAIController();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI);
	UBehaviorTree* BehaviorTree;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI);
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI);
	FName BlackboardTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
