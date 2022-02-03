


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

void UWalletComponent::AddScrap(int64 Amount)
{
	Scrap += Amount;
	OnWalletUpdate.Broadcast();
}

void UWalletComponent::RemoveScrap(int64 Amount)
{ 
	Scrap -= Amount;
	OnWalletUpdate.Broadcast();
}



