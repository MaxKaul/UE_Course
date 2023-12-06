// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"



USTRUCT()
struct FEnemyOptionals
{
	GENERATED_BODY()
public:
	TOptional<class AUE5_BeginnerCourseCharacter*> player;
};

UCLASS()

class UE5_BEGINNERCOURSE_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		virtual void OnPlayerAggro_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void OnPlayerAggro_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx);
	UFUNCTION()
		virtual void OnPlayerDamageRange_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void OnPlayerDamageRange_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyInfo, meta = (AllowPrivateAccess))
		USkeletalMeshComponent* enemyMesh;


	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= EnemyInfo , meta =(AllowPrivateAccess))
		class USphereComponent* aggroCollider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyInfo, meta = (AllowPrivateAccess))
		USphereComponent* damageCollider;

	UPROPERTY()
		FEnemyOptionals enemyOptionals;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
