// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TemporaryPlatform.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

// Sets default values
ATemporaryPlatform::ATemporaryPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh); 

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ATemporaryPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATemporaryPlatform::OnStepOnPlatform);
}


void ATemporaryPlatform::OnStepOnPlatform(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor); 

	if (Character)
	{
		// 이미 밟은 경우 
		if (GetWorldTimerManager().IsTimerActive(DestroyTimer)) return;

		GetWorldTimerManager().SetTimer(
			DestroyTimer,
			this,
			&ATemporaryPlatform::TriggerDestroy,
			TimeToDestroy,
			false 
		);

		if (DestroyOverlayMaterial)
		{
			Mesh->SetOverlayMaterial(DestroyOverlayMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Overlay Material is NULL!")); 
		}
	}

}

void ATemporaryPlatform::TriggerDestroy()
{
	AActor::Destroy();
}



