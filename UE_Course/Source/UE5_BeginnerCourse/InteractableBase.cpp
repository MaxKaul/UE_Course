// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "UE5_BeginnerCourseCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object Mesh");
	RootComponent = objectMesh;

	objectHitBox = CreateDefaultSubobject<UBoxComponent>("Object Collider");
	objectHitBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	objectHitBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::AInteractableBase::OnPlayerInteraction_OnOverlapBegin);
	objectHitBox->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::OnPlayerInteraction_OnOverlapEnd);
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractableBase::OnPlayerInteraction_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (AUE5_BeginnerCourseCharacter* player = Cast<AUE5_BeginnerCourseCharacter>(_otherActor))
		OnPlayerInteract();
}

void AInteractableBase::OnPlayerInteraction_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
	if (AUE5_BeginnerCourseCharacter* player = Cast<AUE5_BeginnerCourseCharacter>(_otherActor))
		OnPlayerInteract();
}

void AInteractableBase::OnPlayerInteract()
{
	bWasInteracted = !bWasInteracted;
}
