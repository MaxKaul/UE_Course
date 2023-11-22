// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractor.h"

#include "MyButton.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerInteractor::UPlayerInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;


	crossHairSize = FVector2D(5.f);
	interactableRange = 1000.f;

	viewPoint = CreateDefaultSubobject<UStaticMeshComponent>("Viewpoint");
}

// Called when the game starts
void UPlayerInteractor::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	owner = Cast<AUE5_BeginnerCourseCharacter>(GetOwner());

	normalMaterial = viewPoint->GetStaticMesh()->GetMaterial(0);

	viewPoint->AttachToComponent(owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Interactable_Socket"));
}

// Called every frame
void UPlayerInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!owner || !world)
		return;

	TraceInteractable();
}


void UPlayerInteractor::TraceInteractable()
{
	FVector worlddir;
	FVector worldpos;

	float crosshairX = UWidgetLayoutLibrary::GetViewportSize(world).X / 2;
	float crosshairY = UWidgetLayoutLibrary::GetViewportSize(world).Y / 3;

	crosshairX -= crossHairSize.X;
	crosshairY -= crossHairSize.Y;

	FVector2D viewportpos = FVector2D(crosshairX, crosshairY);

	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(world, 0), viewportpos, worldpos, worlddir);

	FHitResult hit;

	const TArray<AActor*> emptyactor = { Cast<AActor>(owner) };

	UKismetSystemLibrary::LineTraceSingleByProfile(world, worldpos, worldpos + worlddir * interactableRange, "BlockAll", false, emptyactor, EDrawDebugTrace::None,
		hit, true, FLinearColor::Transparent, FLinearColor::Transparent, 0);

	if (hit.bBlockingHit)
	{
		for (size_t i = 0; i < viewPoint->GetMaterials().Num(); i++)
		{
			if(viewPoint->GetMaterial(i))
				viewPoint->SetMaterial(i, normalMaterial);
		}

		viewPoint->SetWorldLocation(hit.ImpactPoint, false, nullptr, ETeleportType::None);

		if(AMyButton* button = Cast<AMyButton>(hit.GetActor()))
		{
			owner->SetCurrentButton(button);
		}
	}
	else
	{
		for (size_t i = 0; i < viewPoint->GetMaterials().Num(); i++)
		{
			if (viewPoint->GetMaterial(i))
				viewPoint->SetMaterial(i, transMaterial);
		}
	}
}
