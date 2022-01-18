// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ExplosionImpulseComponent.generated.h"

USTRUCT(BlueprintType)
struct FExplosionImpulseInfo
{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 2000.0f;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYSTCORE_API UExplosionImpulseComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UExplosionImpulseComponent();
	
	void Explode(FExplosionImpulseInfo Info);

public:
};
