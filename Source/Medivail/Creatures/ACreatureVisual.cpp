


#include "ACreatureVisual.h"


// Sets default values
AACreatureVisual::AACreatureVisual()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}//test

// Called when the game starts or when spawned
void AACreatureVisual::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AACreatureVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


