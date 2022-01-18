// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplosionImpulseComponent.h"
#include "GameFramework/Actor.h"
#include "ExplosionImpulse.generated.h"

UCLASS()
class MYSTCORE_API AExplosionImpulse : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplosionImpulse();

	UPROPERTY(EditAnywhere);
	UExplosionImpulseComponent* ExplosionImpulseComponent;

	static void CreateAndExplode(UWorld* World, FVector Location, FExplosionImpulseInfo Info);

	void Explode();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
