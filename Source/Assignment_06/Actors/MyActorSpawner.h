// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorSpawner.generated.h"

UCLASS()
class ASSIGNMENT_06_API AMyActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GetRandomLocation(); 
	
	void SpawnActors(); 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<AActor>> SpawnActorClasses; // 스폰할 클래스들 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float Range = 5000.f; // 스폰 범위 

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 SpawnCount = 10; // 스폰 수 
};
