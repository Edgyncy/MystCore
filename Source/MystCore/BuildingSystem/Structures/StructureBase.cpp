// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureBase.h"


AStructureBase::AStructureBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	StructureMesh = CreateDefaultSubobject<USkeletalMeshComponent>("StructureMesh");
	StructureMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PreviewMaterialObj(TEXT("/Game/Characters/BuildingSystem/StructurePreview_Mat"));
	if(PreviewMaterialObj.Succeeded())
	{
		PreviewMaterial = PreviewMaterialObj.Object;
	}

	
	
}

void AStructureBase::BeginPlay()
{
	Super::BeginPlay();

	RealStructureMaterial = StructureMesh->GetMaterial(0);
	StructureMesh->SetMaterial(0, PreviewMaterial);
	StructureMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AStructureBase::PlaceStructure()
{
	StructureMesh->SetMaterial(0, RealStructureMaterial);
	StructureMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bStructureActive = true;
}


void AStructureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

