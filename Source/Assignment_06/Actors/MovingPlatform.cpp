// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MovingPlatform.h"
#include "Engine/TargetPoint.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh; 
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	InitToMove(); 

	const float RandomOffset = FMath::FRandRange(-1.f, 2.f);
	const float FinalCycleTime = FMath::Max(0.1f, HideCycleTime + RandomOffset);

	GetWorld()->GetTimerManager().SetTimer(
		VisibilityTimerHandle,
		this,
		&AMovingPlatform::ChangeVisibility,
		FinalCycleTime,
		true
	);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToTarget(DeltaTime);

}

void AMovingPlatform::InitToMove()
{
	if (bUseTargetActor)
	{
		if (Points.Num() < 2 || Points[0] == nullptr || Points[1] == nullptr)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(0, 1.5, FColor::Red, TEXT("Need More TargetPoint."));
			}
			return;
		}

		SetActorLocation(Points[0]->GetActorLocation());
		
		for (const ATargetPoint* Point : Points)
		{
			if (Point == nullptr) continue; 

			Locations.Add(Point->GetActorLocation()); 
		}

	}
	else
	{
		Locations.Add(GetActorLocation()); 
		Locations.Add(GetRandomLocationInRange(Range));
	}
}


void AMovingPlatform::MoveToTarget(float DeltaTime)
{
	if (Locations.Num() < 2 )
	{
		UE_LOG(LogTemp, Warning, TEXT("Need at least 2 TargetPoints."));
		return; 
	}

	// 방향 구하기 
	FVector CurrentLocation = GetActorLocation();
	FVector PointLocation = Locations[LocationIndex];
	FVector Direction = (PointLocation - CurrentLocation).GetSafeNormal();

	// 다음 위치 
	FVector NewLocation = CurrentLocation + Direction * DeltaTime * MoveSpeed;

	SetActorLocation(NewLocation);

	float distance = FVector::Dist(NewLocation, PointLocation);

	if (distance <= MoveSpeed * DeltaTime)
	{
		LocationIndex = (LocationIndex + 1) % Locations.Num();
	}
}

FVector AMovingPlatform::GetRandomLocationInRange(float InRange)
{
	FVector CurrentLocation = GetActorLocation();

	return FVector(
		CurrentLocation.X + FMath::FRandRange(-Range, Range),
		CurrentLocation.Y + FMath::FRandRange(-Range, Range),
		CurrentLocation.Z + FMath::FRandRange(-Range, Range)
	);
}

void AMovingPlatform::ChangeVisibility()
{
	if (bShouldDisappear)
	{
		SetActorHiddenInGame(!bIsVisible);
		bIsVisible = !bIsVisible;
	}
}

