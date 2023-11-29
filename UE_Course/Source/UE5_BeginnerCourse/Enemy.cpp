// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "AIController.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	enemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Enemy Mesh");
	RootComponent = enemyMesh;

	aggroRadius = CreateDefaultSubobject<USphereComponent>("Aggro Radius");
	aggroRadius->SetupAttachment(GetRootComponent());

	enemyController = CreateDefaultSubobject<AAIController>("Enemy Controller");
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::HuntPlayer()
{
}

void AEnemy::Aggro_OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _overlapActor,
                                  UPrimitiveComponent* _otherComp, int32 _otheridx, bool bSweep, const FHitResult& _sweepResult)
{
	if(!_overlappedComponent->ComponentHasTag("Interactor"))
	{
		if(AUE5_BeginnerCourseCharacter* foundplayer = Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			player = foundplayer;
			bHasFoundPlayer = true;
		}
	}
}

void AEnemy::Aggro_OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComp, int32 _otheridx)
{
	if (!_overlappedComponent->ComponentHasTag("Interactor"))
	{
		if (Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			player = nullptr;
			bHasFoundPlayer = false;
		}
	}
}

