// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionImpulseComponent.h"

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


// Called when the game starts
void UExplosionImpulseComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<FHitResult> HitActors;
	FVector Start = GetComponentLocation();
	FVector End = Start;


	FCollisionShape ShpereCollision = FCollisionShape::MakeSphere(Info.Radius);

	const bool bSweepHit = GetWorld()->SweepMultiByChannel(HitActors, Start,
	                                                       End, FQuat::Identity, ECC_WorldStatic, ShpereCollision);

	if (bSweepHit)
	{
		for (auto& HitActor : HitActors)
		{
			UStaticMeshComponent* Receiver = Cast<UStaticMeshComponent>(HitActor.GetActor()->GetRootComponent());
			if (Receiver)
			{
				Receiver->AddRadialImpulse(Start, Info.Radius, Info.Strength, RIF_Constant, true);
			}
			else
			{
				ACharacter* CharacterReceiver = Cast<ACharacter>(HitActor.GetActor());
				if (CharacterReceiver)
				{
					CharacterReceiver->GetMovementComponent()->AddRadialImpulse(
						Start, Info.Radius, Info.Strength, RIF_Constant, true);
				}
			}
		}
	}
}
