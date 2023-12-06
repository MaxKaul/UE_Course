// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	aggroCollider = CreateDefaultSubobject<USphereComponent>("Aggro Collider");
	aggroCollider->SetupAttachment(GetRootComponent());

	damageCollider = CreateDefaultSubobject<USphereComponent>("Damage Collider");
	damageCollider->SetupAttachment(GetRootComponent());

	bCanAttack = true;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	enemyOptionals = new FEnemyOptionals(this);

	movemenmtComp = GetMovementComponent();

	navigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	enemyMesh = GetMesh();

	enemyController = Cast<AAIController>(GetController());

	aggroCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnPlayerAggro_OnOverlapBegin);
	aggroCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnPlayerAggro_OnOverlapEnd);

	damageCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnPlayerDamageRange_OnOverlapBegin);
	damageCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnPlayerDamageRange_OnOverlapEnd);


	SetState(EEnemyStates::ES_Patrol);
}


void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickState();
}


void AEnemyBase::OnPlayerAggro_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if ( _otherActor->GetClass()->ImplementsInterface(UInterface_Damagable::StaticClass()))
	{
		enemyOptionals->player = Cast<AUE5_BeginnerCourseCharacter>(_otherActor);
		SetState(EEnemyStates::ES_HuntPlayer);
	}
}

void AEnemyBase::OnPlayerAggro_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
	if (_otherActor->GetClass()->ImplementsInterface(UInterface_Damagable::StaticClass()))
	{
		enemyOptionals->player = Cast<AUE5_BeginnerCourseCharacter>(_otherActor);
		SetState(EEnemyStates::ES_Patrol);
	}
}

void AEnemyBase::OnPlayerDamageRange_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (!_otherActor->GetClass()->ImplementsInterface(UInterface_Damagable::StaticClass()))
		return;

	if(enemyOptionals->player.IsSet())
		SetState(EEnemyStates::ES_AttackPlayer);
}

void AEnemyBase::OnPlayerDamageRange_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIdx)
{
	if (enemyOptionals->player.IsSet())
		SetState(EEnemyStates::ES_HuntPlayer);
	else
		SetState(EEnemyStates::ES_Patrol);
}

void AEnemyBase::SetState(EEnemyStates _newState)
{
	currentState = _newState;
}

void AEnemyBase::TickState()
{
	switch (currentState)
	{
	case EEnemyStates::ES_Patrol:
		State_Patrol();
		break;

	case EEnemyStates::ES_HuntPlayer:
		if(enemyOptionals->player.IsSet() && enemyOptionals->player.GetValue())
			State_HuntPlayer();
		break;

	case EEnemyStates::ES_AttackPlayer:
		if(enemyOptionals->player.IsSet() && enemyOptionals->player.GetValue())
			State_AttackPlayer();
		break;

	case EEnemyStates::ES_DEFAULT:
		break;
	case EEnemyStates::ES_MAX_ENTRY: 
		break;
	default: ;
	}
}

void AEnemyBase::State_Patrol()
{
	if (movemenmtComp->Velocity.Length() > 0)
		return;

	FNavLocation navloc;
	navigationSystem->GetRandomPoint(navloc);

	FVector movepos = navloc.Location;

	enemyOptionals->MoveOrder(movepos, TOptional<AActor*>());
}

void AEnemyBase::State_HuntPlayer()
{
	enemyOptionals->MoveOrder(TOptional<FVector>(), enemyOptionals->player.GetValue());
}

void AEnemyBase::State_AttackPlayer()
{
	if (movemenmtComp->Velocity.Length() > 0)
		enemyController->StopMovement();

	if (!enemyOptionals->player.IsSet())
		return;

	if(bCanAttack)
	{
		enemyOptionals->player.GetValue()->TakePlayerDamage(enemyDamage);
		bCanAttack = false;
		handle.Invalidate();
		UE_LOG(LogTemp, Warning, TEXT("Attack"))
	}
	else if(!bCanAttack)
	{
		if (!handle.IsValid())
		{
			UE_LOG(LogTemp,Warning,TEXT("Set Timer"))
			GetWorld()->GetTimerManager().SetTimer(handle, this, &AEnemyBase::ResetCooldown, attackCooldwon);
		}
	}
}

void AEnemyBase::ResetCooldown()
{
	bCanAttack = true;
}

void FEnemyOptionals::MoveOrder(TOptional<FVector> targetPos, TOptional<AActor*> _targetActor)
{
	if (targetPos.IsSet())
		owner->enemyController->MoveToLocation(targetPos.GetValue());
	else if(_targetActor.IsSet())
		owner->enemyController->MoveToActor(_targetActor.GetValue());
}
