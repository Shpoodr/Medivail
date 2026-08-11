

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreatureVisual.generated.h"

class UCreatureaDataAsset;
class UStaticMeshComponent;

UCLASS()
class MEDIVAIL_API ACreatureVisual : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreatureVisual();
	
	UPROPERTY(VisibleAnywhere, Category = "Board")
	int32 Row = 0;

	UPROPERTY(VisibleAnywhere, Category = "Board")
	int32 Lane = 0;

	UPROPERTY(VisibleAnywhere, Category = "Board")
	bool bIsPlayerSide = true;

	UPROPERTY(BlueprintReadOnly, Category = "Creature")
	TObjectPtr<UCreatureDataAsset> CreatureData;

	void InitializeVisual(UCreatureDataAsset* InCreature, int32 Lane, int32 Row, bool bIsPlayerSide);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
