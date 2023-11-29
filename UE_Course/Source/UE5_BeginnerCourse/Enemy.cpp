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

	enemyController = CreateDefaultSubobject<AAIController>("AI Controller");
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

void AEnemy::Aggro_OverlapBegin(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor,
                                UPrimitiveComponent* _otherComponent, int32 _otheridx, bool bSweep, const FHitResult& _sweepResult)
{
	if (!_overlapComponent->ComponentHasTag("Interactor"))
	{
		if(AUE5_BeginnerCourseCharacter* foundPlayer = Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			player = foundPlayer;
			bHasFoundPlayer = true;
			bHasFoundPlayer = true;
		}
	}
}

void AEnemy::Aggro_OverlapEnd(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComponent, int32 _otheridx)
{
	if (!_overlapComponent->ComponentHasTag("Interactor"))
	{
		if (Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			player = nullptr;
			bHasFoundPlayer = false;
		}
	}
}

