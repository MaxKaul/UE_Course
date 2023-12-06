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
	enemyMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>("Enemy Mesh");
	RootComponent = enemyMesh;

	aggroRadius = CreateDefaultSubobject<USphereComponent>("AggroSphere");
	aggroRadius->SetupAttachment(GetRootComponent());

	enemyController = CreateDefaultSubobject<AAIController>("Enemy Contoller");

}

void AEnemy::HuntPlayer()
{
}

void AEnemy::Aggro_OnOverlapBegin(UPrimitiveComponent* _OverlappedComponent, AActor* _overlapActor,
                                  UPrimitiveComponent* _otherComp, int32 _override, bool _sweep, const FHitResult& _sweepResult)
{
	if (_OverlappedComponent->ComponentHasTag("Interactor"))
	{
		if (AUE5_BeginnerCourseCharacter* foundplayer = Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			player = foundplayer;
			bwasfoundPlayer = true;
		}
	}
}

void AEnemy::Aggro_OnOverlapEnd(UPrimitiveComponent* _OverlappedComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComp, int32 _override)
{
	if (_OverlappedComponent->ComponentHasTag("Interactor"))
	{
		if (AUE5_BeginnerCourseCharacter* foundplayer = Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			player = nullptr;
			bwasfoundPlayer = false;
		}
	}

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

