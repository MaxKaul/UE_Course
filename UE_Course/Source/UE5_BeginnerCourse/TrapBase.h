// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapBase.generated.h"

UCLASS()
class UE5_BEGINNERCOURSE_API ATrapBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrapBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void PlayerHit_OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _overlapActor, UPrimitiveComponent* _otherComp, int32 _otheridx, bool bSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void PlayerHit_OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _overlapActor, UPrimitiveComponent* _otherComp, int32 _otheridx);
	UFUNCTION()
		virtual  void MakeDamage(class AUE5_BeginnerCourseCharacter* _player);
	UFUNCTION()
		virtual void ApplyKnockback(AUE5_BeginnerCourseCharacter* _player);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		float knockbackForce;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		float damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		UStaticMeshComponent* objectMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		class UBoxComponent* hitBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		class URotatingMovementComponent* rotator;

public:	
	virtual void Tick(float DeltaTime) override;

};
