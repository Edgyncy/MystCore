


#include "WalletComponent.h"

UWalletComponent::UWalletComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWalletComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWalletComponent::AddScrap(float Amount)
{
	Scrap += FMath::Clamp(Amount, 0.0f, 1000000000.0f);;
	OnWalletUpdate.Broadcast();
}

void UWalletComponent::RemoveScrap(float Amount)
{ 
	Scrap -= FMath::Clamp(Amount, 0.0f, 1000000000.0f);
	OnWalletUpdate.Broadcast();
}



