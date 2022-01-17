// Fill out your copyright notice in the Description page of Project Settings.


#include "BlinkAbility.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MystCore/MystCoreCharacter.h"

ABlinkAbility::ABlinkAbility()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	
	DashLinesFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Dash Lines FX");
	DashLinesFXComponent->SetupAttachment(RootComponent);

	RootComponent->SetWorldLocation(FVector(0.f, 0.f, 0.f));
}


void ABlinkAbility::Cast()
{
	RootComponent->SetWorldLocation(FVector(150.f, 0.f, 0.f));
	RootComponent->SetWorldRotation(FRotator(0,0,0));
	Character = (AMystCoreCharacter*) UGameplayStatics::GetPlayerController(this, 0)->GetCharacter();
	
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	
	AttachToComponent(Character->GetFirstPersonCameraComponent(), TransformRules, TEXT("DashLines"));
	
	FVector Start = Character->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector ImpulseVector = Character->GetVelocity();
	if (FuckZ) ImpulseVector.Z = 0;
	if(ImpulseVector.IsZero() || !BasedOnVelocity)
	{
		ImpulseVector = Character->GetFirstPersonCameraComponent()->GetForwardVector();
	}
	if (FuckZ) ImpulseVector.Z = 0;
	
	ImpulseVector.Normalize();
	ImpulseVector *= BlinkDistance;

	FVector Destination = ImpulseVector + Character->GetActorLocation();

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);
	
	FHitResult result;
	bool ActorHit = GetWorld()->LineTraceSingleByChannel(result, Start, Destination, ECC_Pawn, CollisionParams, FCollisionResponseParams());
	//DrawDebugLine(GetWorld(), Start, Destination, FColor::White);
	
	if(ActorHit)
	{
		//DrawDebugPoint(GetWorld(), result.Location, 10.f, FColor::White);
		Destination = result.Location + (result.Normal * Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.f);
	}

	if(ResetVelocity) Character->LaunchCharacter(FVector(0, 0, 0.01f), false, true);

	Character->SetActorLocation(Destination);

	FinishCasting();
	FTimerHandle UnusedHandle;
	
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABlinkAbility::Delay, 5.f, false);

	//Sound
	ExecuteAbilitySound();
	
	//FOV Animation
	FOVDefault = Character->DefaultFOV;
	GetWorldTimerManager().SetTimer(FOVAnimationTimer, this, &ABlinkAbility::FOVAnimation, FOVAnimationSpeed / 10, true);
}

void ABlinkAbility::FOVAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("Animation: %f"), FOVAnimationAlpha)
	UCameraComponent* camera = Character->GetFirstPersonCameraComponent();
	FOVCurrent = FMath::Lerp(FOVDefault + FOVAnimationScale, FOVDefault, FOVAnimationAlpha);
	FOVAnimationAlpha += FOVAnimationSpeed;

	if(FOVAnimationAlpha >= 1.f)
	{
		GetWorldTimerManager().ClearTimer(FOVAnimationTimer);
		camera->SetFieldOfView(FOVDefault);
		return;
	}
	
	camera->SetFieldOfView(FOVCurrent);
}


void ABlinkAbility::Delay()
{
	Destroy();
}


void ABlinkAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}



