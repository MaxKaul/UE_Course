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
	// Sets default values for this actor's properties
	ATrapBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void PlayerHit_OverlapBegin(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor, UPrimitiveComponent* _otherComponent, int32 _otheridx, bool bSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void PlayerHit_OverlapEnd(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor, UPrimitiveComponent* _otherComponent, int32 _otheridx);
	UFUNCTION()
		virtual void MakeDamage(class AUE5_BeginnerCourseCharacter* _player);
	UFUNCTION()
		virtual void ApplyKnockback(class AUE5_BeginnerCourseCharacter* _player);

protected:
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
