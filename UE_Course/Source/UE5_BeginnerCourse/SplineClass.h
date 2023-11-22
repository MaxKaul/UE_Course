// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineClass.generated.h"

UCLASS()
class UE5_BEGINNERCOURSE_API ASplineClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta =(AllowPrivateAccess))
		class USplineComponent* pathSpline;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() FORCEINLINE
		USplineComponent* GetSplineComponent() { return pathSpline; }
};
