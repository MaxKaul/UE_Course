// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "UE5_BeginnerCourseCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object Mesh");
	RootComponent = objectMesh;

	objectHitbox = CreateDefaultSubobject<UBoxComponent>("Object Collider");
	objectHitbox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	objectHitbox->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::AInteractableBase::OnPlayerInteraction_OnOverlapBegin);
	objectHitbox->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::OnPlayerInteraction_OnOverlapEnd);
	
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

}

void AInteractableBase::OnPlayerInteract()
{
	bWasInteracted = !bWasInteracted;
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

