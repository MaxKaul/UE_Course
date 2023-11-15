// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractor.h"

#include "UE5_BeginnerCourseCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerInteractor::UPlayerInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	crosshairSize = FVector2D(5.f);
	interactableRange = 1000.f;

}


// Called when the game starts
void UPlayerInteractor::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	owner = Cast< AUE5_BeginnerCourseCharacter>(GetOwner());
	
}

void UPlayerInteractor::TraceInteractable()
{

	FVector worlddir;
	FVector worldpos;
	float crosshairX = UWidgetLayoutLibrary::GetViewportSize(world).X / 2;
	float crosshairY = UWidgetLayoutLibrary::GetViewportSize(world).Y / 3;

	crosshairX -= crosshairSize.X;
	crosshairY -= crosshairSize.Y;

	FVector2D viewportpos = FVector2D(crosshairX, crosshairY);
	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(world, 0), viewportpos, worldpos, worlddir);

	FHitResult hit;
	const TArray<AActor*> emptyactor = { Cast<AActor>(owner) };


	UKismetSystemLibrary::LineTraceSingleByProfile(world, worldpos, worldpos + worlddir * interactableRange, "BlockAll", false, emptyactor, EDrawDebugTrace::None, hit, true, FLinearColor::Transparent, FLinearColor::Transparent, 0);

	if(hit.bBlockingHit)
	{
		DrawDebugSphere(world, hit.Location, 16, 16, FColor::Red, false, 1.f, 16, 16);
	}
}


// Called every frame
void UPlayerInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!world||!owner)
	{
		return;
	}

	TraceInteractable();
}

