// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapActor.h"

#include "DrawDebugHelpers.h"
#include "Components/WalletComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AScrapActor::AScrapActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Scarp Mesh");
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh->SetEnableGravity(true);
	StaticMesh->SetSimulatePhysics(true);

	PickupCollision = CreateDefaultSubobject<USphereComponent>("Pickup Collision");
	PickupCollision->SetupAttachment(StaticMesh);
}


// Called when the game starts or when spawned
void AScrapActor::BeginPlay()
{
	Super::BeginPlay();

	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &AScrapActor::OnOverlap);
}

void AScrapActor::PickupScrap(UWalletComponent* WalletComponent, AActor* ToWho)
{
	ScrapState = Attracted;

	PickUpWallet = WalletComponent;
	PickUpActor = ToWho;
	
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetEnableGravity(false);

	StartAnimationLocation = StaticMesh->GetComponentLocation();

	LerpAlpha = 0.0f;
	GetWorldTimerManager().SetTimer(PickupTimer, this, &AScrapActor::PickupAnimationTimer, LerpRate, true);
}

void AScrapActor::PickupAnimationTimer()
{
	LerpAlpha += LerpSpeed;
	BruhLocation = FMath::Lerp(StartAnimationLocation, PickUpActor->GetActorLocation(), LerpAlpha);

	//this->SetActorLocation(BruhLocation);
	StaticMesh->SetWorldLocation(BruhLocation);

	if(LerpAlpha >= 1.0f)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ScrapSound, GetActorLocation());
		PickUpWallet->AddScrap(ScrapHas);
		GetWorldTimerManager().ClearTimer(PickupTimer);
		Destroy();
	}
}


void AScrapActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(ScrapState != Lies) return;
	for(auto& Component : OtherActor->GetComponents())
	{
		if(UWalletComponent* Wallet = Cast<UWalletComponent>(Component))
		{
			PickupScrap(Wallet, OtherActor);
			return;
		}
		
	}
	
}

void AScrapActor::CreateBurst(TSubclassOf<AScrapActor> ScrapType, float Amount, UWorld* World, FVector Location)
{
	int ObjectsAmount = FMath::RandRange(3, 10);

	float AmountPerScrap = Amount / ObjectsAmount;

	for(int count = 0; count < ObjectsAmount; count++)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		AScrapActor* Scrap = World->SpawnActor<AScrapActor>(ScrapType, Location, UKismetMathLibrary::RandomRotator(), params);
		Scrap->ScrapHas = AmountPerScrap;

		UStaticMeshComponent* ScrapStaticMesh = Scrap->StaticMesh;
	
		ScrapStaticMesh->SetAllPhysicsLinearVelocity(ScrapStaticMesh->GetForwardVector() * 1000);
	}

	
	
}


// Called every frame
void AScrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

