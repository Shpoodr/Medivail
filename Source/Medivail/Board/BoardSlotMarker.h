// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardSlotMarker.generated.h"

UCLASS()
class MEDIVAIL_API ABoardSlotMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardSlotMarker();

	UPROPERTY(EditAnywhere, Category = "Board")
	int32 Row = 0;

	UPROPERTY(EditAnywhere, Category = "Board")
	int32 Lane = 0;

	UPROPERTY(EditAnywhere, Category = "Board")
	bool bIsPlayerSide = true;

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
