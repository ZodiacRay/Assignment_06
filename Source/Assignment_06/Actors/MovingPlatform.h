// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class ATargetPoint; 

UCLASS()
class ASSIGNMENT_06_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (allowprivateaccess = true), Category = "Mesh")
	UStaticMeshComponent* Mesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Movement")
	TArray<ATargetPoint*> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Movement")
	bool bUseTargetActor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Movement")
	float MoveSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Movement")
	float Range = 1300.f;

	FVector TargetLocation = FVector::ZeroVector;

	TArray<FVector> Locations; 

	int32 LocationIndex = 0;

protected:
	FTimerHandle VisibilityTimerHandle; 

	bool bIsVisible = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Visiblity")
	bool bShouldDisappear = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Visiblity")
	float HideCycleTime = 3.f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void InitToMove(); 

	void MoveToTarget(float DeltaTime);

	FVector GetRandomLocationInRange(float InRange); 

	void ChangeVisibility(); 

};
