// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/RotatingObstacle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ARotatingObstacle::ARotatingObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh; 

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule")); 
}

// Called when the game starts or when spawned
void ARotatingObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	if (bUseRandomOffset)
	{
		RotateOffset = FRotator(
			FMath::FRandRange(0.f, 100.f),
			FMath::FRandRange(0.f, 100.f),
			FMath::FRandRange(0.f, 100.f)
		);
	}
}

// Called every frame
void ARotatingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	Rotate(DeltaTime);
}

void ARotatingObstacle::NotifyHit(
	UPrimitiveComponent* MyComp,
	AActor* Other, 
	UPrimitiveComponent* OtherComp, 
	bool bSelfMoved, 
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// 캐릭터 인지 확인
	ACharacter* HitCharacter = Cast<ACharacter>(Other);

	if (HitCharacter)
	{
		// 캐릭터 발사할 방향 
		FVector LaunchDirection = HitNormal * -1.0f;
		LaunchDirection.Z = 0.5f;
		LaunchDirection.Normalize();

		// 발사할 세기 
		FVector LaunchVelocity = LaunchDirection * LaunchStrength; 

		HitCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}
}

void ARotatingObstacle::Rotate(float DeltaTime)
{
	const FQuat OldRotation = GetActorQuat();
	const FQuat DeltaRotation = (RotateOffset * DeltaTime).Quaternion();
	const FQuat NewRotation = (OldRotation * DeltaRotation);

	SetActorRotation(NewRotation);
}


