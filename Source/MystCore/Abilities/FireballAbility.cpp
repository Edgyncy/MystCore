// Fill out your copyright notice in the Description page of Project Settings.


#include "FireballAbility.h"

AFireballAbility::AFireballAbility()
{
	
}

void AFireballAbility::BeginPlay()
{
	Super::BeginPlay();
}


void AFireballAbility::Cast()
{
	Super::Cast();

	FinishCasting();
}



