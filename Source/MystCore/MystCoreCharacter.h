// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/CastService.h"
#include "Components/HealthComponent.h"
#include "Components/ManaComponent.h"
#include "GameFramework/Character.h"
#include "Weapons/WeaponBase.h"
#include "MystCoreCharacter.generated.h"

class UAbilityClass;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDealDamage, float, DamageAmount, AActor*, Victim);

UCLASS(BlueprintType, config=Game)
class AMystCoreCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = Jump);
	int JumpHeight = 600.0f;

	UPROPERTY(EditAnywhere, Category = Jump);
	int MaxJumps = 2;

	bool JumpedFromGround = false;

public:
	AMystCoreCharacter();

	/* Events */

	/* On Character Deal Damage (should be broadcasted outside this class wtf0 */
	UPROPERTY(BlueprintAssignable)
	FOnDealDamage OnDealDamage;

protected:
	virtual void BeginPlay();
	
	virtual void PostInitProperties() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	int32 CurrentWeaponIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	TArray<TSubclassOf<AWeaponBase>> WeaponsAvailable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	FName SocketName = FName("s_weaponSocket");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	TArray<AWeaponBase*> WeaponActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultFOV = 110;

	/** Player's Health */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

	/** Player's Mana */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UManaComponent* ManaComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAbilityActor> PrimaryAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAbilityActor> SecondaryAbilityClass;
	
	/** Primary ability **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCastService* PrimaryAbilityService;

	/** Second ability **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCastService* SecondaryAbilityService;
	
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AMystCoreProjectile> ProjectileClass;
	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* JumpAnimation;


protected:
	
	/** Uses Primary Ability. */
	void OnPrimaryAbility();

	/** Uses Secondary Ability. */
	void OnSecondaryAbility();

	/** Switch Weapon Next */
	void SwitchWeaponNext();

	/** Switch Weapon Next */
	void SwitchWeaponPrevious();

	void OnStartFire();

	void OnStopFire();

	bool ChangeWeapon(int32 WeaponIndex);
	
	/** Switch Weapon Next */
	void SwitchWeaponNumber(float Val);
	

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UFUNCTION()
	void OnLandedThing(const FHitResult& Hit);

	UFUNCTION()
	void AdditionalJump();

	UPROPERTY(BlueprintReadOnly)
	int AdditionalJumpCounter;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

