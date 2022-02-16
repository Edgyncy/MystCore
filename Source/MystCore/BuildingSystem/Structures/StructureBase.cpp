// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureBase.h"


AStructureBase::AStructureBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	StructureMesh = CreateDefaultSubobject<USkeletalMeshComponent>("StructureMesh");
	StructureMesh->SetGenerateOverlapEvents(true);
	StructureMesh->SetupAttachment(RootComponent);

	//Cringe part Default Preview Materials
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PreviewMaterialObj(TEXT("/Game/Characters/BuildingSystem/StructurePreview_Mat"));
	if(PreviewMaterialObj.Succeeded())
	{
		PreviewMaterial = PreviewMaterialObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PreviewCantPlaceMaterialObj(TEXT("/Game/Characters/BuildingSystem/StructurePreview_CantPlace_Mat"));
	if(PreviewCantPlaceMaterialObj.Succeeded())
	{
		PreviewCantPlaceMaterial = PreviewCantPlaceMaterialObj.Object;
	}
	//
	
	
}

void AStructureBase::BeginPlay()
{
	Super::BeginPlay();

	RealStructureMaterial = StructureMesh->GetMaterial(0);
	StructureMesh->SetMaterial(0, PreviewMaterial);
	StructureMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StructureMesh->SetCollisionProfileName(FName("Trigger"));

	StructureMesh->OnComponentBeginOverlap.AddDynamic(this, &AStructureBase::OverlapBegin);
	StructureMesh->OnComponentEndOverlap.AddDynamic(this, &AStructureBase::OverlapEnd);
}

void AStructureBase::PlaceStructure()
{
	bPlaced = true;
	StructureMesh->SetMaterial(0, RealStructureMaterial);
	StructureMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StructureMesh->SetCollisionProfileName(FName("BlockAll"));
	bStructureActive = true;
}

void AStructureBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bPlaced) return;
	bOverlapping = true;

	StructureMesh->SetMaterial(0, PreviewCantPlaceMaterial);
}

void AStructureBase::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(bPlaced) return;

	TSet<UPrimitiveComponent*> OverlapComponents; 
	
	StructureMesh->GetOverlappingComponents(OverlapComponents);
	if(OverlapComponents.GetMaxIndex() == 0)
	{
		bOverlapping = false;
		StructureMesh->SetMaterial(0, PreviewMaterial);
	}
}



void AStructureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

