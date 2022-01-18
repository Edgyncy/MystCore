// Copyright Epic Games, Inc. All Rights Reserved.

#include "MystCoreCharacter.h"
#include "MystCoreProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "Abilities/BlinkAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, String)

//////////////////////////////////////////////////////////////////////////
// AMystCoreCharacter

AMystCoreCharacter::AMystCoreCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	PrimaryAbilityService = CreateDefaultSubobject<UCastService>("primary bruh");
	SecondaryAbilityService = CreateDefaultSubobject<UCastService>("second bruh");
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	ManaComponent = CreateDefaultSubobject<UManaComponent>("Mana Component");
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}

void AMystCoreCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	PrimaryAbilityService = NewObject<UCastService>();
	SecondaryAbilityService = NewObject<UCastService>();
}



void AMystCoreCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	GetFirstPersonCameraComponent()->SetFieldOfView(DefaultFOV);
	
	PrimaryAbilityService->AbilityClass = PrimaryAbilityClass;
	SecondaryAbilityService->AbilityClass = SecondaryAbilityClass;

	LandedDelegate.AddDynamic(this, &AMystCoreCharacter::OnLandedThing);

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
	                          TEXT("GripPoint"));
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMystCoreCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMystCoreCharacter::AdditionalJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMystCoreCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMystCoreCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMystCoreCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMystCoreCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMystCoreCharacter::LookUpAtRate);

	//Abilities
	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &AMystCoreCharacter::OnPrimaryAbility);
	PlayerInputComponent->BindAction("SecondaryAbility", IE_Pressed, this, &AMystCoreCharacter::OnSecondaryAbility);
}

void AMystCoreCharacter::OnPrimaryAbility()
{
	//Abilities things
	PrimaryAbilityService->Cast(GetWorld(), this,
		GetFirstPersonCameraComponent()->GetComponentLocation(), GetFirstPersonCameraComponent()->GetComponentRotation());
}

void AMystCoreCharacter::OnSecondaryAbility()
{
	//Abilities things
	SecondaryAbilityService->Cast(GetWorld(), this,
		GetFirstPersonCameraComponent()->GetComponentLocation(), GetFirstPersonCameraComponent()->GetComponentRotation());
}

void AMystCoreCharacter::AdditionalJump()
{
	if(!GetCharacterMovement()->IsFalling()) JumpedFromGround = true;
	int LocalMaxJumps = MaxJumps;

	if(!JumpedFromGround) --LocalMaxJumps;
	
	if (AdditionalJumpCounter < LocalMaxJumps)
	{
		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);

		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(JumpAnimation, 1.f);
		}
	}

	AdditionalJumpCounter++;
}

void AMystCoreCharacter::OnLandedThing(const FHitResult& Hit)
{
	//Reset Jumps
	AdditionalJumpCounter = 0;

	JumpedFromGround = false;
}


void AMystCoreCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if(ManaComponent->Mana <= 100) return;
			ManaComponent->SuckMana(100);
			
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr)
				                               ? FP_MuzzleLocation->GetComponentLocation()
				                               : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AMystCoreProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AMystCoreCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMystCoreCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMystCoreCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMystCoreCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
