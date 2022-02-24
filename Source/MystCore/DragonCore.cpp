// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonCore.h"

// Sets default values
ADragonCore::ADragonCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetRelativeLocation(FVector(0,0,0));

}

// Called when the game starts or when spawned
void ADragonCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADragonCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

