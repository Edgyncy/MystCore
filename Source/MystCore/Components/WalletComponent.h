// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WalletComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWalletUpdate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class MYSTCORE_API UWalletComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties

	UWalletComponent();

	// For HUD purposes
	UPROPERTY(BlueprintAssignable)
	FOnWalletUpdate OnWalletUpdate;

	// Current Currency Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scrap;

	// To add currency
	UFUNCTION()
	void AddScrap(float Amount);

	// To remove currency
	UFUNCTION()
	void RemoveScrap(float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
