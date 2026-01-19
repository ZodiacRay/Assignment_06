// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingObstacle.generated.h"

class URotatingMovementComponent; 
class UCapsuleComponent;


UCLASS()
class ASSIGNMENT_06_API ARotatingObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void Rotate(float DeltaTime);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (allowprivateaccess = true), Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (allowprivateaccess = true), Category = "Mesh")
	UCapsuleComponent* Capsule; 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Offset")
	FRotator RotateOffset = {0.f,0.f,0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Offset")
	bool bUseRandomOffset = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Launch")
	float LaunchStrength = 1000.f;
};
