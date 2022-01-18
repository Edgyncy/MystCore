// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "FallDamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;

	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);

		if(ACharacter* player = dynamic_cast<ACharacter*>(Owner))
		{
			player->LandedDelegate.AddDynamic(this, &UHealthComponent::LandedThing);
		}
	}
	
}

void UHealthComponent::LandedThing(const FHitResult& Hit)
{
	float SpeedZ = FMath::Abs(GetOwner()->GetVelocity().Z);
	if(FallDamageEnabled && SpeedZ >= FallDamageStart)
	{
		float Damage = (SpeedZ - FallDamageStart) * FallDamageMultiplier;
		UGameplayStatics::ApplyDamage(GetOwner(), Damage, nullptr, Hit.GetActor(), UFallDamageType::StaticClass());
	}
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0 || Health == 0)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Damaged: %f"), Damage)
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if(Health == 0)
	{
		OnZeroHealth.Broadcast();
	}
}



