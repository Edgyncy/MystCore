// Fill out your copyright notice in the Description page of Project Settings.


#include "CastService.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UCastService::UCastService()
{
	
}

void UCastService::Cast(UWorld* World, FVector Location, FRotator Rotation)
{
	OnPreCast.Broadcast();
	
	CurrentWorld = World;
	
	UE_LOG(LogTemp, Warning, TEXT("????"));
	if(!IsAvailable)
	{
		OnPostCast.Broadcast(true);
		return;
	}
	AbilityActor = (AAbilityActor*) CurrentWorld->SpawnActor(AbilityClass, &Location, &Rotation);
	
	if(!AbilityActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("WTF Ability Class is not defined"));
		return;
	}

	AbilityActor->OnFinishCast.AddDynamic(this, &UCastService::StartCooldown);
	CooldownTime = AbilityActor->AbilityDetails.Cooldown;
	
	AbilityActor->Cast();

	IsAvailable = false;
	
	OnPostCast.Broadcast(false);
}


void UCastService::StartCooldown()
{
	
	IsAvailable = false;
	EstimatedTime = CooldownTime;

	UE_LOG(LogTemp, Warning, TEXT("Starting Timer.."));
	CurrentWorld->GetTimerManager().SetTimer(UpdateTimer, this, &UCastService::UpdateCooldown, CooldownUpdateRate, true, 0.0f);
	
	OnCooldownStart.Broadcast();
}

void UCastService::UpdateCooldown()
{
	EstimatedTime -= CooldownUpdateRate;

	if(EstimatedTime <= 0)
	{
		EndCooldown();
	}

	UE_LOG(LogTemp, Warning, TEXT("Estimated Timeeeeee: %f"), EstimatedTime)
	OnCooldownUpdate.Broadcast(EstimatedTime, CooldownTime);
}


void UCastService::EndCooldown()
{
	IsAvailable = true;
	CurrentWorld->GetTimerManager().ClearTimer(UpdateTimer);

	OnCooldownEnd.Broadcast();
}





