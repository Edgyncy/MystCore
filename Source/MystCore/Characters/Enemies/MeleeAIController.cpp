// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"

AMeleeAIController::AMeleeAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	PerceptionComponentMelee = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*PerceptionComponentMelee);

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	
}

void AMeleeAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}



