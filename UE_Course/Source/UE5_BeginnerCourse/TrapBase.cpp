// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapBase.h"

#include "UE5_BeginnerCourseCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ATrapBase::ATrapBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	knockbackForce = 500.f;
	damage = 10.f;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = objectMesh;

	hitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	hitBox->SetupAttachment(objectMesh);

	rotator = CreateDefaultSubobject<URotatingMovementComponent>("Rotator");

}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();

	hitBox->OnComponentBeginOverlap.AddDynamic(this, &ATrapBase::PlayerHit_OverlapBegin);
	hitBox->OnComponentEndOverlap.AddDynamic(this, &ATrapBase::PlayerHit_OverlapEnd);
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapBase::PlayerHit_OverlapBegin(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComponent, int32 _otheridx, bool bSweep, const FHitResult& _sweepResult)
{
	if (!_otherComponent->ComponentHasTag("Interactor"))
	{
		if (AUE5_BeginnerCourseCharacter* player = Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
			MakeDamage(player);
	}
}

void ATrapBase::PlayerHit_OverlapEnd(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComponent, int32 _otheridx)
{
}

void ATrapBase::MakeDamage(AUE5_BeginnerCourseCharacter* _player)
{
	_player->TakePlayerDamage(damage);
	ApplyKnockback(_player);
}

void ATrapBase::ApplyKnockback(AUE5_BeginnerCourseCharacter* _player)
{
	if (_player->GetHasDied())
		_player->GetMesh()->AddImpulse(-_player->GetActorForwardVector() * knockbackForce * 50.f + GetActorForwardVector() * knockbackForce * 50.f);
	else
		_player->LaunchCharacter(-_player->GetActorForwardVector() * knockbackForce + GetActorForwardVector() * knockbackForce, true, true);
}