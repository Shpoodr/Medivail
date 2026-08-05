

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACreatureVisual.generated.h"

UCLASS()
class MEDIVAIL_API AACreatureVisual : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACreatureVisual();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
