// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionImpulse.h"


// Sets default values
AExplosionImpulse::AExplosionImpulse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ExplosionImpulseComponent = CreateDefaultSubobject<UExplosionImpulseComponent>("Explosion Component");
	ExplosionImpulseComponent->SetAutoActivate(false);

	RootComponent = ExplosionImpulseComponent;
}

// Called when the game starts or when spawned
void AExplosionImpulse::BeginPlay()
{
	Super::BeginPlay();
}

void AExplosionImpulse::CreateAndExplode(UWorld* World, FVector Location, FExplosionImpulseInfo &Info)
{
	AExplosionImpulse* Impulse = (AExplosionImpulse*) World->SpawnActor(StaticClass(), &Location);
	
	Impulse->Explode(Info);
}


void AExplosionImpulse::Explode(FExplosionImpulseInfo &Info)
{
	ExplosionImpulseComponent->Activate();
	ExplosionImpulseComponent->Explode(Info);
	Destroy();
}


// Called every frame
void AExplosionImpulse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

