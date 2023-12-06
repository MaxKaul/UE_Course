// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "UE5_BeginnerCourseCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	enemyMesh = GetMesh();
	RootComponent = enemyMesh;
	PrimaryActorTick.bCanEverTick = true;
	aggroCollider = CreateDefaultSubobject<USphereComponent>("Aggro Collider");
	aggroCollider->SetupAttachment(RootComponent);

	damageCollider = CreateDefaultSubobject<USphereComponent>("Damage Collider");
	damageCollider->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	aggroCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnPlayerAggro_OnOverlapBegin);
	aggroCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnPlayerAggro_OnOverlapEnd);

	damageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnPlayerDamageRange_OnOverlapBegin);
	damageCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnPlayerDamageRange_OnOverlapEnd);

	
}

void AEnemyBase::OnPlayerAggro_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if(_otherComp->ComponentHasTag("PlayerInteractor"))
	{
			if(AUE5_BeginnerCourseCharacter* targetplayer = Cast<AUE5_BeginnerCourseCharacter>(_otherActor))
			{
				enemyOptionals.player = targetplayer;
				
			}
	}
}

void AEnemyBase::OnPlayerAggro_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
	if (_otherComp->ComponentHasTag("PlayerInteractor"))
	{
		if (AUE5_BeginnerCourseCharacter* targetplayer = Cast<AUE5_BeginnerCourseCharacter>(_otherActor))
		{
			if(enemyOptionals.player.IsSet())
			{
				enemyOptionals.player.Reset();
			}
		}
	}
}

void AEnemyBase::OnPlayerDamageRange_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult)
{
}

void AEnemyBase::OnPlayerDamageRange_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

