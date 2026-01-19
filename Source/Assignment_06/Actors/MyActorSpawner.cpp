// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyActorSpawner.h"

// Sets default values
AMyActorSpawner::AMyActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnActors(); 
}

FVector AMyActorSpawner::GetRandomLocation()
{
	FVector CurrentLocation = GetActorLocation(); 

	FVector Location =
	{
		CurrentLocation.X + FMath::FRandRange(-Range, Range),
		CurrentLocation.Y + FMath::FRandRange(-Range, Range),
		CurrentLocation.Z
	};

	return Location; 
}

void AMyActorSpawner::SpawnActors()
{
	if (SpawnActorClasses.Num() <= 0) return;

	for (int i = 0; i < SpawnCount; i++)
	{
		int32 Index = FMath::RandRange(0, SpawnActorClasses.Num() - 1);

		if (!SpawnActorClasses[Index])
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor Class is Null."));
			return;
		}

		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		UWorld* World = GetWorld();
		if (!World) return;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			SpawnActorClasses[Index],
			GetRandomLocation(),
			FRotator(0, 0, 0),
			Params
		);

		if (!SpawnedActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail to Spawn Actor."));
		}
		else
		{
			SpawnedActor->SetActorScale3D(FVector(
				FMath::FRandRange(0.5f, 5.f),
				FMath::FRandRange(0.5f, 5.f),
				FMath::FRandRange(0.5f, 5.f)
			));

			UE_LOG(LogTemp, Warning, TEXT("Actor Spawned: %s"), *SpawnedActor->GetName());
		}
	}
}

// Called every frame
void AMyActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

