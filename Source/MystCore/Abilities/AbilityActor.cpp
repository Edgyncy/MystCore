// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAbilityActor::AAbilityActor()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/** Don't Super() This XD**/
void AAbilityActor::Cast()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Casting"));

	FinishCasting();
}

void AAbilityActor::FinishCasting()
{
	OnFinishCast.Broadcast();
}



// Called when the game starts or when spawned
void AAbilityActor::BeginPlay()
{
	Super::BeginPlay();

	//Cast();
}

void AAbilityActor::ExecuteAbilitySound()
{
	if (AbilitySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, AbilitySound, GetActorLocation());
	}
}


// Called every frame
void AAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

