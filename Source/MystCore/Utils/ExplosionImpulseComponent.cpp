// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionImpulseComponent.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values for this component's properties
UExplosionImpulseComponent::UExplosionImpulseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UExplosionImpulseComponent::Explode(FExplosionImpulseInfo Info)
{
	TArray<FHitResult> HitActors;
	FVector Start = GetComponentLocation();
	FVector End = Start;


	FCollisionShape SphereCollision = FCollisionShape::MakeSphere(Info.Radius);

	const bool bSweepHit = GetWorld()->SweepMultiByChannel(HitActors, Start,
	                                                       End, FQuat::Identity, ECC_WorldStatic, SphereCollision);

	//DrawDebugSphere(GetWorld(), Start, Info.Radius, 50, FColor::Orange, true);

	if (!bSweepHit) return;
	
	TArray<AActor*> HasBeenHit;
	for (auto& HitActor : HitActors)
	{
		if (!HitActor.GetActor()) continue;

		if (HasBeenHit.Contains(HitActor.GetActor())) continue;
		HasBeenHit.Add(HitActor.GetActor());

		UE_LOG(LogTemp, Warning, TEXT("Character Hit"))
		ACharacter* CharacterReceiver = Cast<ACharacter>(HitActor.GetActor());
		if (CharacterReceiver)
		{
			CharacterReceiver->GetController()->StopMovement();
			CharacterReceiver->GetMovementComponent()->AddRadialImpulse(
				Start, Info.Radius, Info.Strength, RIF_Linear, true);
			continue;
		}

		UStaticMeshComponent* Receiver = Cast<UStaticMeshComponent>(HitActor.GetActor()->GetRootComponent());
		if (Receiver)
		{
			Receiver->AddRadialImpulse(Start, Info.Radius, Info.Strength, RIF_Linear, true);
			continue;
		}
	}
}
