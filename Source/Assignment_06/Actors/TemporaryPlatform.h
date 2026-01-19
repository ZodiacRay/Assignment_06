// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TemporaryPlatform.generated.h"

class UBoxComponent;

UCLASS()
class ASSIGNMENT_06_API ATemporaryPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATemporaryPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	
	UFUNCTION()
	void OnStepOnPlatform(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	void TriggerDestroy();
private: 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (allowprivateaccess = true), Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (allowprivateaccess = true), Category = "Mesh")
	UBoxComponent* BoxCollision;

	FTimerHandle DestroyTimer; 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Destory")
	float TimeToDestroy = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Destory")
	UMaterial* DestroyOverlayMaterial; 
};
