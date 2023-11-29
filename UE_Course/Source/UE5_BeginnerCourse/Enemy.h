// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class UE5_BEGINNERCOURSE_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		UStaticMeshComponent* enemyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		class USphereComponent* aggroRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		class AUE5_BeginnerCourseCharacter* player;

	UPROPERTY()
		bool bHasFoundPlayer;
	UPROPERTY()
		class AAIController* enemyController;

	UFUNCTION()
		void HuntPlayer();


	UFUNCTION()
		virtual void Aggro_OverlapBegin(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor, UPrimitiveComponent* _otherComponent, int32 _otheridx, bool bSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void Aggro_OverlapEnd(UPrimitiveComponent* _overlapComponent, AActor* _overlapActor, UPrimitiveComponent* _otherComponent, int32 _otheridx);

};
