// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineClass.h"

#include "Components/SplineComponent.h"

// Sets default values
ASplineClass::ASplineClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pathSpline = CreateDefaultSubobject<USplineComponent>("Spline Path");
	RootComponent = pathSpline;

}

// Called when the game starts or when spawned
void ASplineClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

