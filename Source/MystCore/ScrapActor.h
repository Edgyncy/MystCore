// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/WalletComponent.h"
#include "GameFramework/Actor.h"
#include "ScrapActor.generated.h"

UENUM()
enum EScrapActorState
{
	Lies,
	Attracted
};

UCLASS()
class MYSTCORE_API AScrapActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AScrapActor();

	EScrapActorState ScrapState = Lies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	float LerpSpeed = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	float LerpRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* PickupCollision;

	float ScrapHas = 69.0f;

	FVector BruhLocation;

	void PickupScrap(UWalletComponent* WalletComponent, AActor* ToWho);

	FTimerHandle PickupTimer;

	UFUNCTION()
	void PickupAnimationTimer();
private:
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector StartAnimationLocation;

	AActor* PickUpActor;
	UWalletComponent* PickUpWallet;

	float LerpAlpha;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static void CreateBurst(TSubclassOf<AScrapActor> ScrapType, float Amount, UWorld* World, FVector Location);
};
