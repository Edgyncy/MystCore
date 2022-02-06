// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyCharacter.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void AMeleeEnemyCharacter::HandPunch()
{
	if(InPunch) return;

	InPunch = true;
	PlayAnimMontage(MeleeAnimation);

	FTimerHandle unused;
	GetWorldTimerManager().SetTimer(unused, this, &AMeleeEnemyCharacter::SetupCollisions, CollisionDetectionDelay, false);
}

void AMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActorDamagedBuffer.Empty();
}


void AMeleeEnemyCharacter::SetupCollisions()
{
	for(auto &Socket : HandSockets)
	{
		FName ObjectName = FName(Socket.ToString() + "_Collision");

		USphereComponent* CollisionShape = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), ObjectName);
		CollisionShape->SetupAttachment(GetMesh(), Socket);
		CollisionShape->SetSphereRadius(DamageRadius);
		CollisionShape->SetCollisionProfileName(FName("OverlapAll"));
		CollisionShape->SetGenerateOverlapEvents(true);
		CollisionShape->RegisterComponent();
		CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &AMeleeEnemyCharacter::OnPunchCollision);
		SphereComponents.Add(CollisionShape);
	}

	FTimerHandle unused;
	GetWorldTimerManager().SetTimer(unused, this, &AMeleeEnemyCharacter::DeleteAllCollisions, PunchDuration, false);
}

void AMeleeEnemyCharacter::DeleteAllCollisions()
{
	for(auto &Component : SphereComponents)
	{
		Component->DestroyComponent();
	}
	SphereComponents.Empty();

	InPunch = false;
}

void AMeleeEnemyCharacter::RemoveActorFromTheBuffer(AActor* ActorToRemove)
{
	ActorDamagedBuffer.Remove(ActorToRemove);
}


void AMeleeEnemyCharacter::OnPunchCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(AEnemyCharacter* v = dynamic_cast<AEnemyCharacter*>(OtherActor)) {
		return;
	}
	
	if(!OtherActor) return;

	if(OtherActor->CanBeDamaged() && !ActorDamagedBuffer.Contains(OtherActor))
	{
		ActorDamagedBuffer.Add(OtherActor);
		UGameplayStatics::ApplyDamage(OtherActor, MeleeDamage, GetInstigatorController(), this, nullptr);
		FTimerHandle unusedshit;
		FTimerDelegate RemoveActorWithDelayThing = FTimerDelegate::CreateUObject(this, &AMeleeEnemyCharacter::RemoveActorFromTheBuffer, OtherActor);
		GetWorldTimerManager().SetTimer(unusedshit, RemoveActorWithDelayThing, DamageCooldownPerActor, false);
	}
	
}

