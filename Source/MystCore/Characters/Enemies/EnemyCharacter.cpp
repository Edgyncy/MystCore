// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "EnemyAIController.h"
#include "MystCore/MystCoreCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	HealthComponent->DefaultHealth = 100;

	AIControllerClass = AEnemyAIController::StaticClass();
}


// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::OnTakeDamage);
	
}

void AEnemyCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	ACharacter* Character = InstigatedBy->GetCharacter();
	if(!Character) return;
	
	AMystCoreCharacter* MSCharacter = Cast<AMystCoreCharacter>(InstigatedBy->GetCharacter());
	if(MSCharacter)
	{
		MSCharacter->OnDealDamage.Broadcast(Damage, this);
	}
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

