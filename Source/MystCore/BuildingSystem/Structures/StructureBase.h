// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructureBase.generated.h"

UCLASS()
class MYSTCORE_API AStructureBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStructureBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	USkeletalMeshComponent* StructureMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	UMaterialInterface* PreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearence)
	UMaterialInterface* PreviewCantPlaceMaterial;

	virtual void PlaceStructure();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	bool bStructureActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	bool bPlaced = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	bool bOverlapping = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UMaterialInterface* RealStructureMaterial;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
