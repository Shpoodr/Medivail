
#include "CreatureVisual.h"
#include "CreatureDataAsset.h"

// Sets default values
ACreatureVisual::ACreatureVisual()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetHiddenInGame(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}//test

// Called when the game starts or when spawned
void ACreatureVisual::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreatureVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACreatureVisual::InitializeBoardVisual(UCreatureDataAsset* InCreature, int32 InRow, int32 InLane, bool bPlayerSide) {
	CreatureData->CardArt = InCreature->CardArt;
}

void ACreatureVisual::InitializeHandVisual() {

}


