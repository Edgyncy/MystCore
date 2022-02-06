// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MeleeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "MeleeEnemyCharacter.generated.h"

UCLASS()
class MYSTCORE_API AMeleeEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void HandPunch();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* MeleeAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollisionDetectionDelay = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PunchDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> HandSockets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MeleeDamage = 10.f;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> ActorDamagedBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageCooldownPerActor = 0.2f;

	UPROPERTY(BlueprintReadOnly)
	bool InPunch = false;

	UFUNCTION()
	void SetupCollisions();

	UFUNCTION()
	void RemoveActorFromTheBuffer(AActor* ActorToRemove);

	UFUNCTION()
	void DeleteAllCollisions();
	
	UPROPERTY(EditAnywhere)	
	TArray<USphereComponent*> SphereComponents;

	UFUNCTION()
	void OnPunchCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	
};
