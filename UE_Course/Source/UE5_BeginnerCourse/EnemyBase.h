// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumLibrary.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"


UCLASS()
class UE5_BEGINNERCOURSE_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnPlayerAggro_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void OnPlayerAggro_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx);

	UFUNCTION()
		virtual void OnPlayerDamageRange_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void OnPlayerDamageRange_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=EnemyInfo,meta=(AllowPrivateAccess))
		USkeletalMeshComponent* enemyMesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = EnemyInfo, meta=(AllowPrivateAccess));
		class USphereComponent* aggroCollider;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = EnemyInfo, meta=(AllowPrivateAccess));
	USphereComponent* damageCollider;

	UPROPERTY()
		EEnemyStates currentState;

	UPROPERTY()
		class UNavigationSystemV1* navigationSystem;

	UPROPERTY()
		class AAIController* enemyController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyInfo, meta = (AllowPrivateAccess))
		float enemyPatrolRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyInfo, meta = (AllowPrivateAccess))
		float enemyDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyInfo, meta = (AllowPrivateAccess))
		float attackCooldwon;

	UPROPERTY()
		 UPawnMovementComponent* movemenmtComp;

	UFUNCTION()
		void SetState(EEnemyStates _newState);

	UFUNCTION()
		void TickState();

	UFUNCTION()
		void State_Patrol();
	UFUNCTION()
		void State_HuntPlayer();
	UFUNCTION()
		void State_AttackPlayer();

	UFUNCTION()
		void ResetCooldown();

	UPROPERTY()
		bool bCanAttack;

	FTimerHandle handle;

	friend struct FEnemyOptionals;

	FEnemyOptionals* enemyOptionals;

public:	
	virtual void Tick(float DeltaTime) override;


};

USTRUCT()
struct FEnemyOptionals
{
	GENERATED_BODY()

	FEnemyOptionals(){};

	FEnemyOptionals(AEnemyBase* _owner) {owner = _owner; }

private:
	AEnemyBase* owner;

public:
	TOptional<class AUE5_BeginnerCourseCharacter*> player;

	void MoveOrder(TOptional<FVector> targetPos, TOptional<AActor*> _targetActor);
};
