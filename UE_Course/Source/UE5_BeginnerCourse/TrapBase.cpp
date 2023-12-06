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

	knockbackforce = 500.f;
	damage = 10.f;
	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = objectMesh;

	hitbox = CreateDefaultSubobject<UBoxComponent>("Hitbox");
	hitbox->SetupAttachment(objectMesh);

	rotator = CreateDefaultSubobject<URotatingMovementComponent>("Rotator");

}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	hitbox->OnComponentBeginOverlap.AddDynamic(this, &ATrapBase::PlayerHit_OnOverlapBegin);
	hitbox->OnComponentEndOverlap.AddDynamic(this, &ATrapBase::PlayerHit_OnOverlapEnd);
	
}

void ATrapBase::PlayerHit_OnOverlapBegin(UPrimitiveComponent* _OverlappedComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComp, int32 _override, bool _sweep, const FHitResult& _sweepResult)
{
	if(!_otherComp->ComponentHasTag("Interactor"))
	{
		if(AUE5_BeginnerCourseCharacter* player = Cast<AUE5_BeginnerCourseCharacter>(_overlapActor))
		{
			MakeDamage(player);
		}
	}
}

void ATrapBase::PlayerHit_OnOverlapEnd(UPrimitiveComponent* _OverlappedComponent, AActor* _overlapActor,
	UPrimitiveComponent* _otherComp, int32 _override)
{

}

void ATrapBase::MakeDamage(AUE5_BeginnerCourseCharacter* _player)
{
	_player->TakePlayerDamage(damage);
	ApplyKockback(_player);
}

void ATrapBase::ApplyKockback(AUE5_BeginnerCourseCharacter* _player)
{
	if(_player->GetHasDied())
	{
		_player->GetMesh()->AddImpulse(-_player->GetActorForwardVector() * knockbackforce * 50 + GetActorForwardVector() * knockbackforce * 50);
	}
	else
	{
		_player->LaunchCharacter(-_player->GetActorForwardVector() * knockbackforce + GetActorForwardVector() * knockbackforce, true, true);
	}
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

