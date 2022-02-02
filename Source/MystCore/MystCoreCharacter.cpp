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

	//Create Wallet
	WalletComponent = CreateDefaultSubobject<UWalletComponent>("Wallet Component");
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

	// Setup Weapons

	for(auto &WeaponClass : WeaponsAvailable)
	{
		AWeaponBase* WeaponBase = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		WeaponBase->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		WeaponBase->SetHidden(true);
		WeaponBase->SetShooter(GetController());
		
		WeaponActors.Add(WeaponBase);
	}

	ChangeWeapon(0);
	
	//

	GetFirstPersonCameraComponent()->SetFieldOfView(DefaultFOV);
	
	PrimaryAbilityService->AbilityClass = PrimaryAbilityClass;
	SecondaryAbilityService->AbilityClass = SecondaryAbilityClass;

	LandedDelegate.AddDynamic(this, &AMystCoreCharacter::OnLandedThing);
	
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

	//
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMystCoreCharacter::OnStartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMystCoreCharacter::OnStopFire);
	
	//
	PlayerInputComponent->BindAction("SwitchWeaponNext", IE_Pressed, this, &AMystCoreCharacter::SwitchWeaponNext);
	PlayerInputComponent->BindAction("SwitchWeaponPrevious", IE_Pressed, this, &AMystCoreCharacter::SwitchWeaponPrevious);
	
	PlayerInputComponent->BindAxis("SwitchWeapon", this, &AMystCoreCharacter::SwitchWeaponNumber);
	
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

void AMystCoreCharacter::OnStartFire()
{
	CurrentWeapon->StartFire();
}

void AMystCoreCharacter::OnStopFire()
{
	CurrentWeapon->StopFire();
}


void AMystCoreCharacter::SwitchWeaponNext()
 {
 	UE_LOG(LogTemp, Warning, TEXT("+1"));
 	if(CurrentWeapon)
 	{
 		if(!ChangeWeapon(CurrentWeaponIndex + 1))
 		{
 				ChangeWeapon(0);
 		}
 	}
 }

void AMystCoreCharacter::SwitchWeaponPrevious()
{
	UE_LOG(LogTemp, Warning, TEXT("-1"));
	if(CurrentWeapon)
	{
		if(!ChangeWeapon(CurrentWeaponIndex - 1))
		{
			{
				ChangeWeapon(WeaponActors.Num() - 1);
			}
		}
	}
}

bool AMystCoreCharacter::ChangeWeapon(int32 WeaponIndex)
{
	if(WeaponIndex < 0) return false;
	if(WeaponIndex > WeaponActors.Num() - 1) return false;
	if(AWeaponBase* DifferentWeapon = WeaponActors[WeaponIndex])
	{
		if(!CurrentWeapon)
		{
			CurrentWeapon = WeaponActors[0];
		}
		CurrentWeapon->SetActiveWeapon(false);
		CurrentWeapon = DifferentWeapon;
		CurrentWeapon->SetActiveWeapon(true);
		
		CurrentWeaponIndex = WeaponIndex;

		return true;
	}
	
	return false;
	
}


void AMystCoreCharacter::SwitchWeaponNumber(float Val)
{
	
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
