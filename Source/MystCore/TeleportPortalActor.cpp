// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPortalActor.h"

#include "MystCoreCharacter.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATeleportPortalActor::ATeleportPortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	PortalFX = CreateDefaultSubobject<UNiagaraComponent>("PortalFX");
	UPointLightComponent* Light = CreateDefaultSubobject<UPointLightComponent>("Light");

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollisionMesh");

	PortalFX->SetupAttachment(RootComponent);
	CollisionMesh->SetupAttachment(RootComponent);
	Light->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void ATeleportPortalActor::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &ATeleportPortalActor::onPortalHit);
	
}

void ATeleportPortalActor::onPortalHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AMystCoreCharacter* player = dynamic_cast<AMystCoreCharacter*>(OtherActor))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TeleportLevel, true);
	}
}



// Called every frame
void ATeleportPortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

