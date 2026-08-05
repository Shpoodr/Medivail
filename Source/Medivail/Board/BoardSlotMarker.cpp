// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BoardSlotMarker.h"

// Sets default values
ABoardSlotMarker::ABoardSlotMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ABoardSlotMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoardSlotMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}