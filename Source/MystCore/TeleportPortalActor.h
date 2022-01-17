// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "TeleportPortalActor.generated.h"

UCLASS()
class MYSTCORE_API ATeleportPortalActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=General)
	UNiagaraComponent* PortalFX;

	UPROPERTY(EditAnywhere, Category=General)
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(EditAnywhere, Category=General)
	FName TeleportLevel;
	//TSoftObjectPtr<UWorld> TeleportLevel;
	
public:	
	// Sets default values for this actor's properties
	ATeleportPortalActor();

	UFUNCTION()
	void onPortalHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
