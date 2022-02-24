// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MystCore/DragonCore.h"

// Sets default values
AEnemyAIController::AEnemyAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*PerceptionComponent);
	
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);

	RunBehaviorTree(BehaviorTree);

	TArray<AActor*> DragonCoreActors;
	UGameplayStatics::GetAllActorsOfClass(this, ADragonCore::StaticClass(), DragonCoreActors);

	if(DragonCoreActors.Max() == 0) return;
	
	GetBlackboardComponent()->SetValueAsObject(BlackboardTarget, DragonCoreActors[0]);
}

void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed())
	{
		if(AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Actor))
		{
			
		}else
		{
			GetBlackboardComponent()->SetValueAsObject(BlackboardTarget, Actor);
		}
	}
}