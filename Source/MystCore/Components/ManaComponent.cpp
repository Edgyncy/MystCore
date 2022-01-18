// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaComponent.h"

UManaComponent::UManaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UManaComponent::RegenerationTimerFunction()
{
	RegenerateMana(RegenerationSpeed / 10);
}

void UManaComponent::SuckMana(float Amount)
{
	Mana = FMath::Clamp(Mana - Amount, 0.0f, DefaultMana);

	OnManaUpdate.Broadcast();
}


void UManaComponent::RegenerateMana(float Amount)
{
	Mana = FMath::Clamp(Mana + Amount, 0.0f, DefaultMana);

	OnManaUpdate.Broadcast();
}


void UManaComponent::BeginPlay()
{
	Super::BeginPlay();

	Mana = DefaultMana;
	GetOwner()->GetWorldTimerManager().SetTimer(RegenerationTimer, this, &UManaComponent::RegenerationTimerFunction, 0.1f, true, 0.0f);

	OnManaUpdate.Broadcast();
}

